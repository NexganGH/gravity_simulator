#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE
#include <cassert>
#include <cmath>
#include <memory>

#include "body.hpp"

class PhysicsEngine {
  // La vera costante è 6.67E-11
 private:
  const double G = 6.67E-11;
  double _timeScale = 1;
  bool _running = false;
  double _timeElapsed = 0;

  void firstStep(std::unique_ptr<Body> &b1, double dt) {
    assert(b1 != nullptr);
    assert(dt >= 0);

    auto pos = b1->getPosition();
    auto vel = b1->getVelocity();

    auto acc = b1->getAcceleration();

    auto newVelocity = vel + acc * dt / 2;

    b1->setVelocity(newVelocity);

    // implementazione eulero
    auto newPosition = pos + vel * dt + 0.5 * acc * std::pow(dt, 2);

    b1->setPosition(newPosition);
  }

  void secondStep(std::unique_ptr<Body> &b1, double dt) {
    assert(b1 != nullptr);
    assert(dt >= 0);

    auto vel = b1->getVelocity();

    auto acc = b1->getAcceleration();

    auto newVelocity =
        vel +
        acc * dt /
            2; 

    b1->setVelocity(newVelocity);
  }

  void applyGravity(std::unique_ptr<Body> &b1, std::unique_ptr<Body> &b2) {
    assert(b1 != nullptr);
    assert(b2 != nullptr);

    auto p1 = b1->getPosition();
    auto p2 = b2->getPosition();
    Vector r = p1 - p2;
    Vector rVersor = r.versor();
    double distance = p1.distance(p2);

    // Formula for gravitational force. See
    // [gravity](https://en.wikipedia.org/wiki/Gravity).
    Vector gForce =
        -G * b1->getMass() * b2->getMass() / std::pow(distance, 2) * rVersor;

    b1->addForce(gForce);
    b2->addForce(-gForce);

    // TODO: Reimplement derivatives.
  }

 public:
  PhysicsEngine(double timeScale) : _timeScale(timeScale) {
    assert(_timeScale >= 0);
  }

  double getTimeScale() { return _timeScale; }

  void setTimeScale(double timeScale) {
    assert(_timeScale >= 0);
    _timeScale = timeScale;
    
  }

  bool isRunning() { return _running; }

  void toggleRunning() { _running = !_running; }

  double getSimulationSecondsElapsed() { return _timeElapsed; }
  double getRealSecondsElapsed() { return _timeElapsed / _timeScale; }

  void resetTimeElapsed() { _timeElapsed = 0; }

  void evolve(std::vector<std::unique_ptr<Body>> &bodies, double dt) {
    assert(dt >= 0);

    dt *= _timeScale * (_running ? 1 : 0);

    // First gravity must be applied.
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      for (auto is = it + 1; is < bodies.end(); ++is) {
        if (it != is) applyGravity(*it, *is);
      }
      firstStep(*it, dt);

      (*it)->resetForce();
    }

    // Forces must be recalculated, as well as new positions (see [Leapfrog
    // integration](https://en.wikipedia.org/wiki/Leapfrog_integration))
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      for (auto is = it + 1; is < bodies.end(); ++is) {
        if (it != is) applyGravity(*it, *is);
      }
      secondStep(*it, dt);
      (*it)->resetForce();
    }

    _timeElapsed += dt;
  }
};

#endif