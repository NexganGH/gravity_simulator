#ifndef BODY_HPP
#define BODY_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "vector.hpp"

class Body {
 protected:
  Vector _position;
  Vector _velocity;
  Vector _force;
  Vector _forceFirstDeriv;
  Vector _forceSecondDeriv;
  double _mass;

 public:
  Body(Vector position, Vector velocity, double mass)
      : _position{position}, _velocity{velocity}, _mass{mass} {
    // TODO: Add class invariants.
  }

  double getMass() const { return _mass; }

  void addForce(Vector force, Vector firstDerivative, Vector secondDerivative) {
    _force += force;
    _forceFirstDeriv += firstDerivative;
    _forceSecondDeriv += secondDerivative;
  }

  Vector getPosition() const { return _position; }

  void setPosition(Vector v) {
    // TODO: Add check that v.x, v.y >= 0.
    _position = v;
  }

  Vector getVelocity() const { return _velocity; }

  void setVelocity(Vector velocity) { _velocity = velocity; }

  void setForce(Vector force) { _force = force; }

  Vector getAcceleration() const { return _force / _mass; }

  Vector getAccelerationFirstDer() const { return _forceFirstDeriv / _mass; }

  Vector getAccelerationSecondDer() const { return _forceSecondDeriv / _mass; }

  void resetForces() {
    _force = {0, 0};
    _forceFirstDeriv = {0, 0};
    _forceSecondDeriv = {0, 0};
  }

  virtual std::unique_ptr<sf::Shape> getShape() const = 0;
};

class Planet : public Body {
 public:
  Planet(Vector position, Vector velocity, double mass)
      : Body(position, velocity, mass) {}

  std::unique_ptr<sf::Shape> getShape() const override {
    auto circle = std::make_unique<sf::CircleShape>(5);
    circle->setFillColor(sf::Color::Blue);

    // Making body's size proportional to mass.
    auto radius = log(getMass()) / 2.5;
    circle->setRadius(radius);
    circle->setPosition(_position.x - radius, _position.y - radius);
    // circle->setPosition(_position.x, _position.y);
    return circle;
  }
};

#endif