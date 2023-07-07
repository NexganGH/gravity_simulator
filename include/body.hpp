#ifndef BODY_HPP
#define BODY_HPP

#include <SFML/Graphics.hpp>
#include <cassert>
#include <cmath>
#include <iostream>

#include "vector.hpp"

namespace gs {

/**
 * Represents a generic body in the simulation with a given position, velocity,
 * force and mass.
 */
class Body {
 protected:
  Vector _position;
  Vector _velocity;
  Vector _force;
  double _mass;

 public:
  Body(Vector position, Vector velocity, double mass);

  /**
   * @return The mass of the body.
   */
  double getMass() const;

  /**
   * @return The position of the body in universe's coordinates.
   */
  Vector getPosition() const;

  /**
   * Sets the position of the body
   *
   * @param v The new position.
   */
  void setPosition(Vector v);

  /**
   * @return The current velocity of the body.
   */
  Vector getVelocity() const;

  /**
   * Sets the velocity of the body.
   *
   * @param velocity The new velocity.
   */
  void setVelocity(Vector velocity);

  /**
   * Add a force to the body (without resetting the current force).
   *
   * @param force The force to add.
   * @see [Force](https://en.wikipedia.org/wiki/Force)
   */
  void addForce(Vector force);

  /**
   * Calculates the acceleration of the body according to Newton's Second Law Of
   * Motion.
   *
   * @return The current acceleration.
   * @see [Newton's laws of
   * motion](https://en.wikipedia.org/wiki/Newton%27s_laws_of_motion)
   */
  Vector getAcceleration() const;

  /**
   * Sets the force applied to this body to 0.
   */
  void resetForce();

  /**
   * Creates a shape for the body. The shape will automatically be scaled
   * according to the universe's scale.
   *
   * The position of the shape is in universe's coordinates.
   *
   * @param scale The scale of the universe compared to the screen.
   * @return A pointer to the created shape.
   */
  virtual std::unique_ptr<sf::Shape> getShape(double scale) const = 0;

  /**
   * Clones the body.
   *
   * @return A pointer to a clone of the body.
   */
  virtual std::unique_ptr<Body> clone() const = 0;

  virtual ~Body() = default;
};

/**
 * Represents a generic Planet in the space. Planets have random colors.
 */
class Planet : public Body {
 private:
  sf::Color _color;

 public:
  Planet(Vector position, Vector velocity, double mass);

  std::unique_ptr<sf::Shape> getShape(double scale) const override;

  std::unique_ptr<Body> clone() const override;
};

class Star : public Body {
 public:
  Star(Vector position, Vector velocity, double mass);

  std::unique_ptr<sf::Shape> getShape(double scale) const override;

  std::unique_ptr<Body> clone() const override;
};

};  // namespace gs

#endif