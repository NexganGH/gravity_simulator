#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <vector>

#include "SFML/Graphics.hpp"
#include "body.hpp"
#include "configuration.hpp"
#include "renderer.hpp"
namespace gs {

auto CreateSolarSystem(sf::RenderWindow& window) {
  const float EARTH_SUN_DISTANCE = 149597870700;
  const float EARTH_SPEED = 30.24E3;
  const float EARTH_MASS = 5.9722E24;
  const float SUN_MASS = 1.98855E30;

  const float MERCURY_AFELIO = 69.8E9;
  const float MERCURY_AFELIO_SPEED = 39.0E3;
  const float MERCURY_MASS = 0.055 * EARTH_MASS;

  const float MOON_AFELIO = 405500E3;
  const float MOON_AFELIO_SPEED = 0.970E3;
  const float MOON_MASS = 7.3476E22;

  const float VENUS_AFELIO = 109.8E9;
  const float VENUS_AFELIO_SPEED = 34.78E3;
  const float VENUS_MASS = 0.815 * EARTH_MASS;

  const float MARS_AFELIO = 249.261E9;
  const float MARS_AFELIO_SPEED = 21.97E3;
  const float MARS_MASS = 0.1 * EARTH_MASS;

  const float JUPITER_AFELIO = 816.363E9;
  const float JUPITER_AFELIO_SPEED = 12.44E3;
  const float JUPITER_MASS = 318 * EARTH_MASS;

  const float NEPTUNE_AFELIO = 30.34 * EARTH_SUN_DISTANCE;
  const float NEPTUNE_AFELIO_SPEED = 5.37E3;
  const float NEPTUNE_MASS = 17 * EARTH_MASS;

  auto SolarSystem = std::make_shared<Configuration>(
      "Solar System", 3 * MARS_AFELIO, 1000000, window);

  auto height = 3 * MARS_AFELIO;

  std::unique_ptr<Body> sun = std::make_unique<Planet>(
      Vector{height / 2, height / 2}, Vector{0, 0}, SUN_MASS);
  std::unique_ptr<Body> earth = std::make_unique<Planet>(
      Vector{height / 2 + EARTH_SUN_DISTANCE, height / 2},
      Vector{0, -EARTH_SPEED}, EARTH_MASS);
  std::unique_ptr<Body> mercury =
      std::make_unique<Planet>(Vector{height / 2 - MERCURY_AFELIO, height / 2},
                               Vector{0, MERCURY_AFELIO_SPEED}, MERCURY_MASS);
  std::unique_ptr<Body> venus =
      std::make_unique<Planet>(Vector{height / 2 - VENUS_AFELIO, height / 2},
                               Vector{0, VENUS_AFELIO_SPEED}, VENUS_MASS);
  std::unique_ptr<Body> mars =
      std::make_unique<Planet>(Vector{height / 2 - MARS_AFELIO, height / 2},
                               Vector{0, MARS_AFELIO_SPEED}, MARS_MASS);

  std::unique_ptr<Body> moon = std::make_unique<Planet>(
      Vector{height / 2 + EARTH_SUN_DISTANCE + MOON_AFELIO, height / 2},
      Vector{0, -MOON_AFELIO_SPEED - EARTH_SPEED}, MOON_MASS);
  // std::unique_ptr<Body> jupiter = std::make_unique<Planet>(
  //     Vector{0.5 * 1E5 + JUPITER_AFELIO + JUPITER_AFELIO / 2- JUPITER_AFELIO,
  //            height / 2},
  //     Vector{0, JUPITER_AFELIO_SPEED}, JUPITER_MASS);
  // std::unique_ptr<Body> neptune = std::make_unique<Planet>(
  //     Vector{0.5 * 1E5 + NEPTUNE_AFELIO + NEPTUNE_AFELIO / 2- NEPTUNE_AFELIO,
  //            height / 2},
  //     Vector{0, NEPTUNE_AFELIO_SPEED}, NEPTUNE_MASS);

  SolarSystem->addBody(sun);
  SolarSystem->addBody(earth);
  SolarSystem->addBody(mercury);
  SolarSystem->addBody(venus);
  SolarSystem->addBody(mars);
  SolarSystem->addBody(moon);
  // SolarSystem->addBody(neptune);

  return SolarSystem;
}

auto CreateEarthAndSun(sf::RenderWindow& window) {
  const float EARTH_SUN_DISTANCE = 149597870700;
  const float EARTH_SPEED = 30.24E3;
  const float EARTH_MASS = 5.9722E24;
  const float SUN_MASS = 1.98855E30;

  auto EarthAndSun = std::make_shared<Configuration>(
      "Earth & Sun", 3 * EARTH_SUN_DISTANCE, 1000000, window);

  auto height = 2 * EARTH_SUN_DISTANCE;
  auto width = 3 * EARTH_SUN_DISTANCE;

  std::unique_ptr<Body> sun = std::make_unique<Planet>(
      Vector{width / 2, height / 2}, Vector{0, 0}, SUN_MASS);
  std::unique_ptr<Body> earth = std::make_unique<Planet>(
      Vector{width / 2 + EARTH_SUN_DISTANCE, height / 2},
      Vector{0, -EARTH_SPEED}, EARTH_MASS);

  EarthAndSun->addBody(sun);
  EarthAndSun->addBody(earth);

  return EarthAndSun;
}

void CreateStarCollision(std::vector<std::shared_ptr<Configuration>> list,
                         sf::RenderWindow& window) {
  const float EARTH_SUN_DISTANCE = 149597870700;
  const float EARTH_SPEED = 30.24E3;
  const float EARTH_MASS = 5.9722E24;
  const float SUN_MASS = 1.98855E30;

  auto StarCollision = new Configuration(
      "Star Collision", 3 * EARTH_SUN_DISTANCE, 1000000, window);

  auto height = 3 * EARTH_SUN_DISTANCE;

  std::unique_ptr<Body> sun = std::make_unique<Planet>(
      Vector{height / 2, height / 2}, Vector{0, 0}, SUN_MASS);
  std::unique_ptr<Body> earth = std::make_unique<Planet>(
      Vector{height / 2 + EARTH_SUN_DISTANCE, height / 2},
      Vector{0, -EARTH_SPEED}, EARTH_MASS);
  std::unique_ptr<Body> star = std::make_unique<Planet>(
      Vector{height / 2 - height / 4, height / 2 + height / 4},
      Vector{0, -EARTH_SPEED * 2}, 5E30);

  StarCollision->addBody(sun);
  StarCollision->addBody(earth);
  StarCollision->addBody(star);

  list.push_back(std::unique_ptr<Configuration>(StarCollision));
}

void CreateStableOrbitTwoPlanets(
    std::vector<std::shared_ptr<Configuration>> list,
    sf::RenderWindow& window) {
  auto StableOrbitTwoPlanets =
      new Configuration("Two Planets", 1600, 1000000, window);
  std::unique_ptr<Body> p1 =
      std::make_unique<Planet>(Vector{800, 400} * 100, Vector{0, 0}, 10E15);
  std::unique_ptr<Body> p2 =
      std::make_unique<Planet>(Vector{500, 400} * 100, Vector{0, 45}, 10E13);

  StableOrbitTwoPlanets->addBody(p1);
  StableOrbitTwoPlanets->addBody(p2);

  list.push_back(std::unique_ptr<Configuration>(StableOrbitTwoPlanets));
}

void CreateStableOrbitTwoPlanets2(
    std::vector<std::shared_ptr<Configuration>> list,
    sf::RenderWindow& window) {
  auto StableOrbitTwoPlanets2 =
      new Configuration("Two Planets 2", 1600, 1000000, window);
  std::unique_ptr<Body> p1 =
      std::make_unique<Planet>(Vector{800, 400} * 100, Vector{0, 0}, 10E16);
  std::unique_ptr<Body> p2 =
      std::make_unique<Planet>(Vector{800, 100} * 100, Vector{-180, 0}, 10E11);

  StableOrbitTwoPlanets2->addBody(p1);
  StableOrbitTwoPlanets2->addBody(p2);

  list.push_back(std::unique_ptr<Configuration>(StableOrbitTwoPlanets2));
}

auto CreateThreeBodies(sf::RenderWindow& window) {
  auto ThreeBodies =
      std::make_shared<Configuration>("Three Bodies", 2000, 1000000, window);

  std::unique_ptr<Body> p1 =
      std::make_unique<Planet>(Vector{700, 400}, Vector{0, 30}, 10E14);
  std::unique_ptr<Body> p2 =
      std::make_unique<Planet>(Vector{1000, 400}, Vector{0, 0}, 50E14);

  std::unique_ptr<Body> p3 =
      std::make_unique<Planet>(Vector{1200, 500}, Vector{10, 30}, 10E14);

  ThreeBodies->addBody(p1);
  ThreeBodies->addBody(p2);
  ThreeBodies->addBody(p3);

  return ThreeBodies;
}

void CreateBinaryStars(std::vector<std::shared_ptr<Configuration>> list,
                       sf::RenderWindow& window) {
  auto BinaryStars = new Configuration("Binary Stars", 2000, 1000000, window);

  std::unique_ptr<Body> s1 =
      std::make_unique<Planet>(Vector{975, 400}, Vector{0, 25}, 20E14);
  std::unique_ptr<Body> s2 =
      std::make_unique<Planet>(Vector{1100, 400}, Vector{0, -25}, 20E14);

  BinaryStars->addBody(s1);
  BinaryStars->addBody(s2);

  list.push_back(std::unique_ptr<Configuration>(BinaryStars));
}

void CreateCollapsingBinaryStars(
    std::vector<std::shared_ptr<Configuration>> list,
    sf::RenderWindow& window) {
  auto CollapsingBinaryStars =
      new Configuration("Collapsing Binary Stars", 2000, 1000000, window);

  std::unique_ptr<Body> s1 =
      std::make_unique<Planet>(Vector{850, 400}, Vector{0, 20}, 50E14);
  std::unique_ptr<Body> s2 =
      std::make_unique<Planet>(Vector{1150, 400}, Vector{0, -20}, 50E14);

  CollapsingBinaryStars->addBody(s1);
  CollapsingBinaryStars->addBody(s2);

  list.push_back(std::unique_ptr<Configuration>(CollapsingBinaryStars));
}

std::vector<std::shared_ptr<Configuration>> getConfigurations(
    sf::RenderWindow& window) {
  std::vector<std::shared_ptr<Configuration>> list;

  list.push_back(CreateSolarSystem(window));
  list.push_back(CreateEarthAndSun(window));
  list.push_back(CreateThreeBodies(window));

  return list;
}

};  // namespace gs
#endif