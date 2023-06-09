#ifndef BODY_HPP
#define BODY_HPP

#include <SFML/Graphics.hpp>

struct Vector {
  double x;
  double y;
};

class Body {
 protected:
  Vector _position;
  Vector _velocity;
  Vector _acceleration;
  double _mass;

 public:
  Body(Vector position, Vector velocity, double mass)
      : _position{position}, _velocity{velocity}, _mass{mass} {
    // TODO: Add class invariants.
  }

  Vector getPosition() {
    return _position;
  }

  void setPosition(Vector v) {
    // TODO: Add check that v.x, v.y >= 0.
    _position = v;
  }

  Vector getVelocity() {
    return _velocity;
  }

  virtual std::unique_ptr<sf::Shape> getShape() = 0;
};

class Planet : public Body {
 public:
  Planet(Vector position, Vector velocity, double mass) : Body(position, velocity, mass) {

  }


  std::unique_ptr<sf::Shape> getShape() override {
    auto circle = new sf::CircleShape(5);
    circle->setFillColor(sf::Color::Blue);
    circle->setPosition(_position.x, _position.y);

    return std::unique_ptr<sf::Shape>(circle);
  }
};

#endif