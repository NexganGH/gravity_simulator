#ifndef BODY_HPP
#define BODY_HPP

#include <SFML/Graphics.hpp>
#include <cassert>
#include <cmath>
#include <iostream>

#include "vector.hpp"

class Body {
 protected:
  Vector _position;
  Vector _velocity;
  Vector _force;
  double _mass;

 public:
  Body(Vector position, Vector velocity, double mass);

  double getMass() const;

  Vector getPosition() const;
  void setPosition(Vector v);
  Vector getVelocity() const;
  void setVelocity(Vector velocity);

  void addForce(Vector force);

  Vector getAcceleration() const;
  void resetForce();
  virtual std::unique_ptr<sf::Shape> getShape(double scale) const = 0;

  virtual std::unique_ptr<Body> clone() const = 0;
};

class Planet : public Body {
 public:
  Planet(Vector position, Vector velocity, double mass);

  std::unique_ptr<sf::Shape> getShape(double scale) const override;

  std::unique_ptr<Body> clone() const override;
};

#endif