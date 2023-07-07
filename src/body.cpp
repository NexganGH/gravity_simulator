#include "body.hpp"

#include <SFML/Graphics.hpp>
#include <cassert>
#include <cmath>
#include <iostream>

#include "constants.hpp"
#include "vector.hpp"

namespace gs {

Body::Body(Vector position, Vector velocity, double mass)
    : _position{position}, _velocity{velocity}, _mass{mass} {
  if (mass <= 0) throw std::invalid_argument("Scale must be > 0");
}

double Body::getMass() const { return _mass; }

Vector Body::getPosition() const { return _position; }

void Body::setPosition(Vector v) { _position = v; }

Vector Body::getVelocity() const { return _velocity; }

void Body::setVelocity(Vector velocity) { _velocity = velocity; }

void Body::addForce(Vector force) { _force += force; }

Vector Body::getAcceleration() const { return _force / _mass; }

void Body::resetForce() { _force = {0, 0}; }

Planet::Planet(Vector position, Vector velocity, double mass)
    : Body(position, velocity, mass),
      _color(
          sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255)) {}

std::unique_ptr<sf::Shape> Planet::getShape(double scale) const {
  if (scale <= 0) throw std::invalid_argument("Scale must be > 0");

  auto circle = std::make_unique<sf::CircleShape>(1);
  circle->setFillColor(_color);

  // Making body's size proportional to mass.
  auto radius = std::pow(getMass(), 0.08) * 1E8;

  // We must rescale the REAL radius to the SCREEN radius (REAL = meters;
  // SCREEN = pixels)
  circle->setRadius(radius / scale);
  circle->setPosition(_position.x, _position.y);
  return circle;
}

std::unique_ptr<Body> Planet::clone() const {
  return std::make_unique<Planet>(*this);
}

Star::Star(Vector position, Vector velocity, double mass)
    : Body(position, velocity, mass) {}

std::unique_ptr<sf::Shape> Star::getShape(double scale) const {
  if (scale <= 0) throw std::invalid_argument("Scale must be > 0");

  // Making body's size proportional to mass.

  auto circle = std::make_unique<sf::CircleShape>(1);

  // Gives the color according to the mass.
  if (_mass <= SUN_MASS) {
    circle->setFillColor(sf::Color::Yellow);
  } else if (_mass <= 10 * SUN_MASS) {
    circle->setFillColor(sf::Color(255, 215, 0));
  } else {
    circle->setFillColor(sf::Color::Red);
  }

  auto radius = std::pow(getMass(), 0.08) * 1E8;
  circle->setRadius(radius / scale);
  circle->setPosition(_position.x, _position.y);
  return circle;
}

std::unique_ptr<Body> Star::clone() const {
  return std::make_unique<Star>(*this);
}

};  // namespace gs