#ifndef BODY_HPP
#define BODY_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <cassert>

#include "vector.hpp"

class Body {
 protected:
  Vector _position;
  Vector _velocity;
  Vector _force;
  double _mass;

 public:
  Body(Vector position, Vector velocity, double mass)
      : _position{position}, _velocity{velocity}, _mass{mass} {
    assert(_mass>0);
  }

  double getMass() const { return _mass; } //

  Vector getPosition() const { return _position; }//

  void setPosition(Vector v) { _position = v; }//

  Vector getVelocity() const { return _velocity; }//

  void setVelocity(Vector velocity) { _velocity = velocity; }//

  void addForce(Vector force) { _force += force; }//

  Vector getAcceleration() const { return _force / _mass; }// chekc if the mass is different from zero, already tested if the mass is non positive

  void resetForce() { _force = {0, 0}; }//

  virtual std::unique_ptr<sf::Shape> getShape(double scale) const = 0;

  virtual std::unique_ptr<Body> clone() const = 0;
};

class Planet : public Body {
 public:
  Planet(Vector position, Vector velocity, double mass)
      : Body(position, velocity, mass) {}

  std::unique_ptr<sf::Shape> getShape(double scale) const override {
    assert(scale > 0);

    auto circle = std::make_unique<sf::CircleShape>(5);
    circle->setFillColor(sf::Color::Blue);

    // Making body's size proportional to mass.
    auto radius = std::pow(getMass(), 0.08) * 1E8;
    circle->setRadius(radius / scale);
    circle->setPosition(_position.x, _position.y);
    return circle;
  }
  
  std::unique_ptr<Body> clone() const override {
    return std::make_unique<Planet>(*this);
  }
};

#endif