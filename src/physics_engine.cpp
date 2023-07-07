#include "physics_engine.hpp"

#include <cassert>
#include <cmath>
#include <memory>

namespace gs {

void PhysicsEngine::firstStep(std::unique_ptr<Body> &b1, double dt) const {
  assert(b1 != nullptr);
  assert(dt >= 0);

  auto pos = b1->getPosition();
  auto vel = b1->getVelocity();

  auto acc = b1->getAcceleration();

  auto newVelocity = vel + acc * dt / 2;

  b1->setVelocity(newVelocity);

  // implementazione eulero
  auto newPosition = pos + newVelocity * dt;

  b1->setPosition(newPosition);
}

void PhysicsEngine::secondStep(std::unique_ptr<Body> &b1, double dt) const {
  assert(b1 != nullptr);
  assert(dt >= 0);

  auto vel = b1->getVelocity();

  auto acc = b1->getAcceleration();

  auto newVelocity = vel + acc * dt / 2;

  b1->setVelocity(newVelocity);
}

void PhysicsEngine::applyGravity(std::unique_ptr<Body> &b1,
                                 std::unique_ptr<Body> &b2) const {
  if (b1 == nullptr) throw new std::invalid_argument("b1 must be non-null.");
  if (b2 == nullptr) throw new std::invalid_argument("b2 must be non-null.");

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
  if (timeScale <= 0) throw std::invalid_argument("timeScale must be >= 0");
}

double PhysicsEngine::getTimeScale() const { return _timeScale; }

void PhysicsEngine::setTimeScale(double timeScale) {
  if (timeScale < 0) throw std::invalid_argument("timeScale must be >= 0");
  _timeScale = timeScale;
}

bool PhysicsEngine::isRunning() const { return _running; }

void PhysicsEngine::toggleRunning() { _running = !_running; }

double PhysicsEngine::getSimulationSecondsElapsed() const {
  return _timeElapsed;
}
double PhysicsEngine::getRealSecondsElapsed() const {
  return _timeElapsed / _timeScale;
}

void PhysicsEngine::evolve(std::vector<std::unique_ptr<Body>> &bodies,
                           double dt) {
  if (dt < 0) throw new std::invalid_argument("dt must be >= 0.");

  dt *= _timeScale * (_running ? 1 : 0);

  // First gravity must be applied to all, first step.
  for (auto it = bodies.begin(); it != bodies.end(); ++it) {
    for (auto is = it + 1; is < bodies.end(); ++is) {
      if (it != is) {
        applyGravity(*it, *is);
      }
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

};  // namespace gs