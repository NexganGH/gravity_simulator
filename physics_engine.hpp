#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE
#include "body.hpp"
#include<memory>

class PhysicsEngine {
  public:
    void evolve(std::shared_ptr<Body> b1, double dt) {
      auto pos = b1->getPosition();
      auto vel = b1->getVelocity();
      auto newPosition = Vector { pos.x + vel.x * dt, pos.y + vel.y * dt};
      b1->setPosition(newPosition);
    }
};

#endif