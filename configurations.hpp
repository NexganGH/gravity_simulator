#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <vector>

#include "body.hpp"

void stableOrbitTwoPlanets(std::vector<std::unique_ptr<Body>>& bodies) {
  std::unique_ptr<Body> p1 =
      std::make_unique<Planet>(Vector{800, 400}, Vector{0, 0}, 10E15);
  std::unique_ptr<Body> p2 =
      std::make_unique<Planet>(Vector{500, 400}, Vector{0, 45}, 10E13);

  bodies.push_back(std::move(p1));
  bodies.push_back(std::move(p2));
}

void threeBodies(std::vector<std::unique_ptr<Body>> & bodies) {
   std::unique_ptr<Body> p2 =
      std::make_unique<Planet>(Vector{500, 400}, Vector{0, 30}, 10E14);
  std::unique_ptr<Body> p1 =
      std::make_unique<Planet>(Vector{800, 400}, Vector{0, 0}, 50E14);
 
std::unique_ptr<Body> p3 =
      std::make_unique<Planet>(Vector{1000, 500}, Vector{10, 30}, 10E14);
  

  bodies.push_back(std::move(p1));
  bodies.push_back(std::move(p2));
  bodies.push_back(std::move(p3));
}

void binaryStars(std::vector<std::unique_ptr<Body>> & bodies) {
  std::unique_ptr<Body> p1 =
      std::make_unique<Planet>(Vector{575, 400}, Vector{0, 25}, 20E14);
  std::unique_ptr<Body> p2 =
      std::make_unique<Planet>(Vector{700, 400}, Vector{0, -25}, 20E14);

  bodies.push_back(std::move(p1));
  bodies.push_back(std::move(p2));
}

void collapsingBinaryStars(std::vector<std::unique_ptr<Body>> & bodies) {
  std::unique_ptr<Body> p1 =
      std::make_unique<Planet>(Vector{500, 400}, Vector{0, 20}, 50E14);
  std::unique_ptr<Body> p2 =
      std::make_unique<Planet>(Vector{800, 400}, Vector{0, -20}, 50E14);

  bodies.push_back(std::move(p1));
  bodies.push_back(std::move(p2));
}

#endif