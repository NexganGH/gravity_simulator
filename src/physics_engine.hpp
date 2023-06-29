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
    auto pos = b1->getPosition();
    auto vel = b1->getVelocity();

    auto acc = b1->getAcceleration();
    auto acc1 = b1->getAccelerationFirstDer();
    auto acc2 = b1->getAccelerationSecondDer();

    auto newVelocity =
        vel +
        acc * dt /
            2;  //+ 0.5 * acc1 * pow(dt/2, 2);// + (1 / 6) * acc2 * pow(dt, 3);

    // vel.x = vel.x + acc.x * dt + 0.5 * acc1.x * dt * dt;
    // vel.y = vel.y + acc.y * dt + 0.5 * acc1.y * dt * dt;
    b1->setVelocity(newVelocity);

    // implementazione eulero
    auto newPosition = pos + vel * dt + 0.5 * acc * pow(dt, 2) +
                       (1 / 6) * acc1 * pow(dt, 3) +
                       (1 / 24) * acc2 * pow(dt, 4);

    b1->setPosition(newPosition);

    _timeElapsed += dt;
  }

  void secondStep(std::unique_ptr<Body> &b1, double dt) {
    auto vel = b1->getVelocity();

    auto acc = b1->getAcceleration();
    // auto acc1 = b1->getAccelerationFirstDer();
    // auto acc2 = b1->getAccelerationSecondDer();

    auto newVelocity =
        vel +
        acc * dt /
            2;  //+ 0.5 * acc1 * pow(dt/2, 2);// + (1 / 6) * acc2 * pow(dt, 3);

    // vel.x = vel.x + acc.x * dt + 0.5 * acc1.x * dt * dt;
    // vel.y = vel.y + acc.y * dt + 0.5 * acc1.y * dt * dt;
    b1->setVelocity(newVelocity);
  }

  void applyGravity(std::unique_ptr<Body> &b1, std::unique_ptr<Body> &b2) {
    auto p1 = b1->getPosition();
    auto p2 = b2->getPosition();
    Vector r = p1 - p2;
    Vector rVersor = r.versor();
    double distance = p1.distance(p2);

    // Formula for gravitational force. See
    // [gravity](https://en.wikipedia.org/wiki/Gravity).
    Vector gForce =
        -G * b1->getMass() * b2->getMass() / std::pow(distance, 2) * rVersor;

    // Vector oVersor{-rVersor.x, rVersor.y};

    // auto v{b1->getVelocity()};
    //  Vector firstDer = G * m1 * m2 * 2 * (r.x * v.x + r.y * v.y) /
    //(pow(r.x * r.x + r.y * r.y, 2)) * rVersor -
    //     G *m1 *m2 / (pow(r.norm(), 2)) * oVersor;
    //  Vector firstDeri

    b1->addForce(gForce, {0, 0}, {0, 0});
    b2->addForce(-gForce, {0, 0}, {0, 0});

    // TODO: Reimplement derivatives.
  }

 public:
  PhysicsEngine(double timeScale) : _timeScale(timeScale) {
    assert(_timeScale >= 0);
  }

  void setTimeScale(double timeScale) {
    _timeScale = timeScale;
    assert(_timeScale >= 0);
  }

  bool isRunning() { return _running; }

  void toggleRunning() { _running = !_running; }

  double getSecondsElapsed() { return _timeElapsed; }

  void evolve(std::vector<std::unique_ptr<Body>> &bodies, double dt) {
    dt *= _timeScale * (_running ? 1 : 0);

    // First gravity must be applied.
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      for (auto is = it + 1; is < bodies.end(); ++is) {
        if (it != is) applyGravity(*it, *is);
      }
      firstStep(*it, dt);

      (*it)->resetForces();
    }

    // Forces must be recalculated, as well as new positions (see [Leapfrog integration](https://en.wikipedia.org/wiki/Leapfrog_integration))
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      for (auto is = it + 1; is < bodies.end(); ++is) {
        if (it != is) applyGravity(*it, *is);
      }
      secondStep(*it, dt);
      (*it)->resetForces();
    }
  }
};

#endif