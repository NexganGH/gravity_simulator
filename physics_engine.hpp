#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE
#include "body.hpp"
#include<memory>
#include<cmath>

class PhysicsEngine {
  const float G = 10;
  
  public:
    void applyGravity(std::unique_ptr<Body>& b1, std::unique_ptr<Body>& b2) {
    }

    void evolve(std::unique_ptr<Body>& b1, double dt) {
      auto pos = b1->getPosition();
      auto vel = b1->getVelocity();

      auto acc = b1->getAcceleration();
      

      auto newPosition = Vector { pos.x + vel.x * dt + std::pow((acc.x), 2)/2 * dt, pos.y + vel.y * dt + std::pow(acc.y, 2)/2 * dt};
      b1->setPosition(newPosition);

      vel.x = vel.x + acc.x * dt;
      vel.y = vel.y + acc.y * dt;
      b1->setVelocity(vel);
    }
};

#endif