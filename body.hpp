#ifndef BODY_HPP
#define BODY_HPP

#include <SFML/Graphics.hpp>

struct Vector {
  double x;
  double y;
};

class Body {
 private:
  Vector _position;
  Vector _velocity;
  Vector _acceleration;
  double _mass;

 public:
    Body(Vector position, Vector velocity, double mass) : _position{position}, _velocity{velocity}, _mass{mass} {
      // TODO: Add class invariants.
    }

    virtual sf::Shape getShape() = 0;

};

#endif