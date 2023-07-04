
#include <cassert>
#include <cmath>
#include <memory>

#include "../include/body.hpp"
#include "../include/physics_engine.hpp"



  void PhysicsEngine::firstStep(std::unique_ptr<Body> &b1, double dt) {
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

  void PhysicsEngine::secondStep(std::unique_ptr<Body> &b1, double dt) {
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

  void PhysicsEngine::applyGravity(std::unique_ptr<Body> &b1, std::unique_ptr<Body> &b2) {
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

 
  PhysicsEngine::PhysicsEngine(double timeScale) : _timeScale(timeScale) {
    assert(_timeScale >= 0);
  }

  double PhysicsEngine::getTimeScale() { return _timeScale; }

  void PhysicsEngine::setTimeScale(double timeScale) {
    assert(_timeScale >= 0);
    _timeScale = timeScale;
    
  }

  bool PhysicsEngine::isRunning() { return _running; }

  void PhysicsEngine::toggleRunning() { _running = !_running; }

  double PhysicsEngine::getSimulationSecondsElapsed() { return _timeElapsed; }
  double PhysicsEngine::getRealSecondsElapsed() { return _timeElapsed / _timeScale; }

  void PhysicsEngine::resetTimeElapsed() { _timeElapsed = 0; }

  void PhysicsEngine::evolve(std::vector<std::unique_ptr<Body>> &bodies, double dt) {
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
