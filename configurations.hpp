#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <vector>

#include "body.hpp"
#include "renderer.hpp"

Renderer earthAndSun(std::vector<std::unique_ptr<Body>>& bodies,
                     sf::RenderWindow& window) {
  const float EARTH_SUN_DISTANCE = 149597870700;
  const float EARTH_SPEED = 30.24E3;
  const float EARTH_MASS = 5.9722E24;
  const float SUN_MASS = 1.98855E30;

  auto renderer = Renderer::fromUniverseWidth(
      window, 2 * EARTH_SUN_DISTANCE + EARTH_SUN_DISTANCE);

  auto height = renderer.getUniverseHeight();

  std::unique_ptr<Body> sun = std::make_unique<Planet>(
      Vector{0.5 * 1E5 + EARTH_SUN_DISTANCE + EARTH_SUN_DISTANCE / 2,
             height / 2},
      Vector{0, 0}, SUN_MASS);
  std::unique_ptr<Body> earth = std::make_unique<Planet>(
      Vector{0.5 * 1E5 + EARTH_SUN_DISTANCE * 2 + EARTH_SUN_DISTANCE / 2,
             height / 2},
      Vector{0, -EARTH_SPEED}, EARTH_MASS);

  bodies.push_back(std::move(sun));
  bodies.push_back(std::move(earth));

  return renderer;
}

Renderer starCollision(std::vector<std::unique_ptr<Body>>& bodies,
                       sf::RenderWindow& window) {
  const float EARTH_SUN_DISTANCE = 149597870700;
  const float EARTH_SPEED = 30.24E3;
  const float EARTH_MASS = 5.9722E24;
  const float SUN_MASS = 1.98855E30;

  auto renderer = Renderer::fromUniverseWidth(
      window, 2 * EARTH_SUN_DISTANCE + EARTH_SUN_DISTANCE);

  auto height = renderer.getUniverseHeight();

  std::unique_ptr<Body> sun = std::make_unique<Planet>(
      Vector{0.5 * 1E5 + EARTH_SUN_DISTANCE + EARTH_SUN_DISTANCE / 2,
             height / 2},
      Vector{0, 0}, SUN_MASS);
  std::unique_ptr<Body> earth = std::make_unique<Planet>(
      Vector{0.5 * 1E5 + EARTH_SUN_DISTANCE * 2 + EARTH_SUN_DISTANCE / 2,
             height / 2},
      Vector{0, -EARTH_SPEED}, EARTH_MASS);
  std::unique_ptr<Body> star = std::make_unique<Planet>(
      Vector{0.5 * 1E5 + EARTH_SUN_DISTANCE + EARTH_SUN_DISTANCE,
             height / 2 + height / 4},
      Vector{0, -EARTH_SPEED * 2}, 5E30);

  bodies.push_back(std::move(sun));
  bodies.push_back(std::move(earth));
  bodies.push_back(std::move(star));

  return renderer;
}

void stableOrbitTwoPlanets(std::vector<std::unique_ptr<Body>>& bodies) {
  std::unique_ptr<Body> p1 =
      std::make_unique<Planet>(Vector{800, 400} * 100, Vector{0, 0}, 10E15);
  std::unique_ptr<Body> p2 =
      std::make_unique<Planet>(Vector{500, 400} * 100, Vector{0, 45}, 10E13);

  bodies.push_back(std::move(p1));
  bodies.push_back(std::move(p2));
}

void stableOrbitTwoPlanets2(std::vector<std::unique_ptr<Body>>& bodies) {
  std::unique_ptr<Body> p1 =
      std::make_unique<Planet>(Vector{800, 400} * 100, Vector{0, 0}, 10E16);
  std::unique_ptr<Body> p2 =
      std::make_unique<Planet>(Vector{800, 100} * 100, Vector{-180, 0}, 10E11);

  bodies.push_back(std::move(p1));
  bodies.push_back(std::move(p2));
}

void threeBodies(std::vector<std::unique_ptr<Body>>& bodies) {
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

void binaryStars(std::vector<std::unique_ptr<Body>>& bodies) {
  std::unique_ptr<Body> p1 =
      std::make_unique<Planet>(Vector{575, 400}, Vector{0, 25}, 20E14);
  std::unique_ptr<Body> p2 =
      std::make_unique<Planet>(Vector{700, 400}, Vector{0, -25}, 20E14);

  bodies.push_back(std::move(p1));
  bodies.push_back(std::move(p2));
}

void collapsingBinaryStars(std::vector<std::unique_ptr<Body>>& bodies) {
  std::unique_ptr<Body> p1 =
      std::make_unique<Planet>(Vector{500, 400}, Vector{0, 20}, 50E14);
  std::unique_ptr<Body> p2 =
      std::make_unique<Planet>(Vector{800, 400}, Vector{0, -20}, 50E14);

  bodies.push_back(std::move(p1));
  bodies.push_back(std::move(p2));
}

#endif