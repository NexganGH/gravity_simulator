#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE
#include "body.hpp"
#include<memory>
#include<cmath>

class PhysicsEngine {
  const float G = 6.67430E-11;
  
  public:
    void applyGravity(std::unique_ptr<Body>& b1, std::unique_ptr<Body>& b2) {
    }

    void evolve(std::unique_ptr<Body>& b1, double dt) {
      auto pos = b1->getPosition();
      auto vel = b1->getVelocity();

      auto acc = b1->getAcceleration();
      

      auto newPosition = Vector { pos.x + vel.x * dt + 0.5*acc.x*std::pow(dt,2), pos.y + vel.y * dt + 0.5 * acc.y*std::pow(dt,2)};
      b1->setPosition(newPosition);

      vel.x = vel.x + acc.x * dt;
      vel.y = vel.y + acc.y * dt;
      b1->setVelocity(vel);
    }
};

#endif