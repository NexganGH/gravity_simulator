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
  Vector _force_deriv;
  // mod
  Vector _force_2deriv;
  double _mass;

 public:
  Body(Vector position, Vector velocity, double mass)
      : _position{position}, _velocity{velocity}, _mass{mass} {
    // TODO: Add class invariants.
  }

  double getMass() const { return _mass; }

  void addForce(Vector f) { _force = _force + f; }


  void setForce_deriv(Vector a) { _force_deriv = a; }
  Vector getAccDer() {
    return {_force_deriv.x / _mass, _force_deriv.y / _mass};
  }

  // mod
  void setForce2deriv(Vector a) { _force_2deriv = a; }
  Vector getAcc2der() {
    return {_force_2deriv.x / _mass, _force_2deriv.x / _mass};
  }
  void setForce2derivUp(Vector a) { _force_2deriv = _force_2deriv + a; }
  // mod

  
  void setForce_derivUp(Vector f) { _force_deriv = _force_deriv + f; }

  Vector getPosition() const { return _position; }

  void setPosition(Vector v) {
    // TODO: Add check that v.x, v.y >= 0.
    _position = v;
  }

  Vector getVelocity() const { return _velocity; }

  void setVelocity(Vector velocity) { _velocity = velocity; }

  Vector getForce() const { return _force; }

  void setForce(Vector force) { _force = force; }

  Vector getAcceleration() const {
    return {_force.x / _mass, _force.y / _mass};
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
    auto radius = sqrt(getMass()) * 10E-7 / 2.5;
    circle->setRadius(radius);
    circle->setPosition(_position.x - radius, _position.y - radius);
    // circle->setPosition(_position.x, _position.y);
    return circle;
  }
};

#endif