
#include "../include/body.hpp"

#include <SFML/Graphics.hpp>
#include <cassert>
#include <cmath>
#include <iostream>

#include "vector.hpp"
#include "body.hpp"
 
  Body::Body(Vector position, Vector velocity, double mass)
      : _position{position}, _velocity{velocity}, _mass{mass} {
    assert(_mass>0);
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
    : Body(position, velocity, mass) {}

// qui non ci vanno gli overrride
std::unique_ptr<sf::Shape> Planet::getShape(double scale) const {
  assert(scale > 0);

  auto circle = std::make_unique<sf::CircleShape>(5);
  circle->setFillColor(sf::Color::Blue);

  // Making body's size proportional to mass.
  auto radius = std::pow(getMass(), 0.08) * 1E8;
  circle->setRadius(radius / scale);
  circle->setPosition(_position.x, _position.y);
  return circle;
}

std::unique_ptr<Body> Planet::clone() const {
  return std::make_unique<Planet>(*this);
}
