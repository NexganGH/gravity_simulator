#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

struct Vector {
  double x;
  double y;


  /**
   * Calculates the euclidean norm of the vector.
   * 
   * @return the norm of the vector.
   * @see [Euclidean Norm](https://en.wikipedia.org/wiki/Euclidean_norm)
  */
  double norm() {
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
  }

  /**
   * Calculates the euclidean distance between this vector and `v2`.
   * 
   * @return the distance of the vector.
   * @see [Euclidean Distance](https://en.wikipedia.org/wiki/Euclidean_distance)
  */
  double distance(Vector v2);
  
};

// D//overload operatore somma per vector
Vector operator+(Vector a, Vector b) { return {a.x + b.x, a.y + b.y}; }

Vector operator-(Vector a, Vector b) { return {a.x - b.x, a.y - b.y}; }

Vector operator-(Vector v) { return Vector {0, 0} - v; }

Vector operator*(double k, Vector v) { return {v.x * k, v.y * k}; }

Vector operator*(Vector v, double k) { return k * v; }

double Vector::distance(Vector v2) {
  return (*this-v2).norm();
}

#endif