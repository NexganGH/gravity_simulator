#ifndef VECTOR_H
#define VECTOR_H

#include <SFML/Graphics.hpp>
#include <cmath>

namespace gs {

/**
 * A vector in a 2D space.
 *
 * @see [Vector](https://en.wikipedia.org/wiki/Vector)
 */
struct Vector {
  double x{0};
  double y{0};

  /**
   * Calculates the euclidean norm of the vector.
   *
   * @return the norm of the vector.
   * @see [Euclidean norm](https://en.wikipedia.org/wiki/Euclidean_norm)
   */
  double norm() const;

  /**
   * Calculates the euclidean distance between this vector and `v2`.
   *
   * @return the distance of the vector.
   * @see [Euclidean distance](https://en.wikipedia.org/wiki/Euclidean_distance)
   */
  double distance(Vector v2) const;

  /**
   * Calculates the versor (or unit vector) of this vector.
   *
   * @return the versor of the vector.
   * @see [Unit vector](https://en.wikipedia.org/wiki/Unit_vector)
   */
  Vector versor() const;

  sf::Vector2f toSfml() const;

  Vector& operator+=(const Vector& v);
  bool operator==(const Vector& b) const;
};

// D//overload operatore somma per vector
Vector operator+(Vector a, Vector b);

Vector operator-(Vector a, Vector b);
Vector operator-(Vector v);

Vector operator*(double k, Vector v);

Vector operator*(Vector v, double k);

Vector operator/(Vector v, double k);
};  // namespace gs
#endif