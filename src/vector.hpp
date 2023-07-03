#ifndef VECTOR_H
#define VECTOR_H

#include <SFML/Graphics.hpp>
#include <cmath>

struct Vector {
  double x;
  double y;

  /**
   * Calculates the euclidean norm of the vector.
   *
   * @return the norm of the vector.
   * @see [Euclidean norm](https://en.wikipedia.org/wiki/Euclidean_norm)
   */
  double norm() const { return std::sqrt(std::pow(x, 2) + std::pow(y, 2)); }

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
  Vector versor() const ;

  sf::Vector2f toSfml() const { return sf::Vector2f(x, y); }

  Vector& operator+=(const Vector& v) {
    this->x = x + v.x;
    this->y = y + v.y;
    return *this;
  }

  bool operator==(const Vector& b) const {
    return (*this).x == b.x && (*this).y == b.y;
  }
};
//creo una struct di vettori
struct Cuple_Vector{
  Vector pos;
  Vector vel;
};

// D//overload operatore somma per vector
Vector operator+(Vector a, Vector b) { return {a.x + b.x, a.y + b.y}; }

Vector operator-(Vector a, Vector b) { return {a.x - b.x, a.y - b.y}; }

Vector operator-(Vector v) { return Vector{0, 0} - v; }

Vector operator*(double k, Vector v) { return {v.x * k, v.y * k}; }

Vector operator*(Vector v, double k) { return k * v; }

Vector operator/(Vector v, double k) { return v * (1 / k); }

double Vector::distance(Vector v2) const { return (*this - v2).norm(); }

Vector Vector::versor() const {
  auto norm = this->norm();

  if (norm == 0)
    throw std::invalid_argument("The vector does not have a valid versor (the vector is {0, 0}).");

  return (*this) / norm; 
}

#endif