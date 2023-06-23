#ifndef BODY_HPP
#define BODY_HPP

#include <SFML/Graphics.hpp>

struct Vector {
  double x;
  double y;
};

//D//overload operatore somma per vector
Vector operator+(Vector a, Vector b){return {a.x+b.x, a.y+b.y};}

class Body {
 protected:
  Vector _position;
  Vector _velocity;
  Vector _force;
  Vector _force_deriv;
  double _mass;

 public:
  Body(Vector position, Vector velocity, double mass)
      : _position{position}, _velocity{velocity}, _mass{mass} {
    // TODO: Add class invariants.
  }

  //MODIFICHE//
  double getMass() { return _mass; }
  void setForce_deriv(Vector a) { _force_deriv = a; }
  Vector getAccDer(){return {_force_deriv.x/_mass, _force_deriv.y/_mass};}

  void setForceUp(Vector f){_force=_force+f;}
  void setForce_derivUp(Vector f){_force_deriv=_force_deriv+f;}
  //MODIFICHE//

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
    return { _force.x / _mass, _force.y / _mass };
  }

  virtual std::unique_ptr<sf::Shape> getShape() const = 0;
};

class Planet : public Body {
 public:
  Planet(Vector position, Vector velocity, double mass)
      : Body(position, velocity, mass) {}

  std::unique_ptr<sf::Shape> getShape() const override {
    std::unique_ptr<sf::Shape> circle = std::make_unique<sf::CircleShape>(5);
    circle->setFillColor(sf::Color::Blue);
    circle->setPosition(_position.x, _position.y);
    return circle;
  }
};

#endif