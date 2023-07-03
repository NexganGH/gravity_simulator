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
    assert(_mass>0);
  }

  double getMass() const { return _mass; }

  Vector getPosition() const { return _position; }

  void setPosition(Vector v) { _position = v; }

  Vector getVelocity() const { return _velocity; }

  void setVelocity(Vector velocity) { _velocity = velocity; }

  void addForce(Vector force, Vector firstDerivative, Vector secondDerivative) {
    _force += force;
    _forceFirstDeriv += firstDerivative;
    _forceSecondDeriv += secondDerivative;
  }

  Vector getAcceleration() const { return _force / _mass; }

  Vector getAccelerationFirstDer() const { return _forceFirstDeriv / _mass; }

  Vector getAccelerationSecondDer() const { return _forceSecondDeriv / _mass; }

  void resetForces() {
    _force = {0, 0};
    _forceFirstDeriv = {0, 0};
    _forceSecondDeriv = {0, 0};
  }

  virtual std::unique_ptr<sf::Shape> getShape(double scale) const = 0;
};

class Planet : public Body {
 public:
  Planet(Vector position, Vector velocity, double mass)
      : Body(position, velocity, mass) {}

  std::unique_ptr<sf::Shape> getShape(double scale) const override {
    auto circle = std::make_unique<sf::CircleShape>(5);
    circle->setFillColor(sf::Color::Blue);

    // Making body's size proportional to mass.
    auto radius = std::pow(getMass(), 0.08) * 1E8;
    circle->setRadius(radius / scale);
    circle->setPosition(_position.x, _position.y);
    return circle;
  }
};

#endif