#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <vector>

#include "SFML/Graphics.hpp"
#include "body.hpp"
#include "configuration.hpp"
#include "constants.hpp"
#include "renderer.hpp"

namespace gs {

auto createSolarSystem(sf::RenderWindow& window) {
  auto solarSystem = std::make_shared<Configuration>(
      "Solar System", 2 * NEPTUNE_AFELIO + EARTH_SUN_DISTANCE, 1000000, window);

  auto height = 2 * NEPTUNE_AFELIO + EARTH_SUN_DISTANCE;

  std::unique_ptr<Body> sun = std::make_unique<Star>(
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
  std::unique_ptr<Body> jupiter =
      std::make_unique<Planet>(Vector{height / 2 + JUPITER_AFELIO, height / 2},
                               Vector{0, -JUPITER_AFELIO_SPEED}, JUPITER_MASS);
  std::unique_ptr<Body> neptune =
      std::make_unique<Planet>(Vector{height / 2 + NEPTUNE_AFELIO, height / 2},
                               Vector{0, -NEPTUNE_AFELIO_SPEED}, NEPTUNE_MASS);
  std::unique_ptr<Body> uranus =
      std::make_unique<Planet>(Vector{height / 2 + URANUS_AFELIO, height / 2},
                               Vector{0, -URANUS_AFELIO_SPEED}, URANUS_MASS);
  std::unique_ptr<Body> saturn =
      std::make_unique<Planet>(Vector{height / 2 - SATURN_AFELIO, height / 2},
                               Vector{0, SATURN_AFELIO_SPEED}, SATURN_MASS);

  solarSystem->addBody(sun);
  solarSystem->addBody(mercury);
  solarSystem->addBody(venus);
  solarSystem->addBody(earth);
  solarSystem->addBody(moon);
  solarSystem->addBody(mars);
  solarSystem->addBody(jupiter);
  solarSystem->addBody(saturn);
  solarSystem->addBody(uranus);
  solarSystem->addBody(neptune);

  return solarSystem;
}

auto createSolarSystemTillMars(sf::RenderWindow& window) {
  auto solarSystemTillMars = std::make_shared<Configuration>(
      "Solar System till Mars", 3 * MARS_AFELIO, 1000000, window);

  auto height = 3 * MARS_AFELIO;

  std::unique_ptr<Body> sun = std::make_unique<Star>(
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

  solarSystemTillMars->addBody(sun);
  solarSystemTillMars->addBody(earth);
  solarSystemTillMars->addBody(mercury);
  solarSystemTillMars->addBody(venus);
  solarSystemTillMars->addBody(mars);
  solarSystemTillMars->addBody(moon);

  return solarSystemTillMars;
}

auto createEarthAndSun(sf::RenderWindow& window) {
  auto earthAndSun = std::make_shared<Configuration>(
      "Earth & Sun", 3 * EARTH_SUN_DISTANCE, 1000000, window);

  auto height = 3 * EARTH_SUN_DISTANCE;

  std::unique_ptr<Body> sun = std::make_unique<Star>(
      Vector{height / 2, height / 2}, Vector{0, 0}, SUN_MASS);
  std::unique_ptr<Body> earth = std::make_unique<Planet>(
      Vector{height / 2 + EARTH_SUN_DISTANCE, height / 2},
      Vector{0, -EARTH_SPEED}, EARTH_MASS);
  std::unique_ptr<Body> moon = std::make_unique<Planet>(
      Vector{height / 2 + EARTH_SUN_DISTANCE + MOON_AFELIO, height / 2},
      Vector{0, -MOON_AFELIO_SPEED - EARTH_SPEED}, MOON_MASS);

  earthAndSun->addBody(sun);
  earthAndSun->addBody(earth);
  earthAndSun->addBody(moon);

  return earthAndSun;
}

auto createStarCollapsing(sf::RenderWindow& window) {
  auto starCollapsing = std::make_shared<Configuration>(
      "Star Collapsing", 3 * EARTH_SUN_DISTANCE, 1000000, window);

  auto height = 3 * EARTH_SUN_DISTANCE;

  std::unique_ptr<Body> sun = std::make_unique<Star>(
      Vector{height / 2, height / 2}, Vector{0, 0}, SUN_MASS);
  std::unique_ptr<Body> earth = std::make_unique<Planet>(
      Vector{height / 2 + EARTH_SUN_DISTANCE, height / 2},
      Vector{0, -EARTH_SPEED}, EARTH_MASS);
  std::unique_ptr<Body> moon = std::make_unique<Planet>(
      Vector{height / 2 + EARTH_SUN_DISTANCE + MOON_AFELIO, height / 2},
      Vector{0, -MOON_AFELIO_SPEED - EARTH_SPEED}, MOON_MASS);
  std::unique_ptr<Body> star = std::make_unique<Star>(
      Vector{height / 2 - height / 4, height / 2 + height / 4},
      Vector{0, -EARTH_SPEED * 2}, 5E30);

  starCollapsing->addBody(sun);
  starCollapsing->addBody(earth);
  starCollapsing->addBody(moon);
  starCollapsing->addBody(star);

  return starCollapsing;
}

auto createThreeBodies(sf::RenderWindow& window) {
  auto threeBodies = std::make_shared<Configuration>(
      "Three Planets", 3 * MARS_AFELIO, 1000000, window);

  auto height = 3 * MARS_AFELIO;

  std::unique_ptr<Body> p1 = std::make_unique<Planet>(
      Vector{height / 2 - VENUS_AFELIO, height / 2 + MERCURY_AFELIO},
      Vector{0, 0}, JUPITER_MASS);
  std::unique_ptr<Body> p2 = std::make_unique<Planet>(
      Vector{height / 2 + VENUS_AFELIO, height / 2 + MERCURY_AFELIO},
      Vector{0, 0}, SATURN_MASS);
  std::unique_ptr<Body> p3 =
      std::make_unique<Planet>(Vector{height / 2, height / 2 - VENUS_AFELIO},
                               Vector{10, 30}, 0.8 * JUPITER_MASS);

  threeBodies->addBody(p1);
  threeBodies->addBody(p2);
  threeBodies->addBody(p3);

  return threeBodies;
}

auto createBinaryStars(sf::RenderWindow& window) {
  auto binaryStars = std::make_shared<Configuration>(
      "Binary Stars", 3 * MARS_AFELIO, 1000000, window);
  auto height = 3 * MARS_AFELIO;
  std::unique_ptr<Body> s1 = std::make_unique<Star>(
      Vector{height / 2 - EARTH_SUN_DISTANCE, height / 2},
      Vector{0, 0.5 * EARTH_SPEED}, 0.75 * SUN_MASS);
  std::unique_ptr<Body> s2 = std::make_unique<Star>(
      Vector{height / 2 + EARTH_SUN_DISTANCE, height / 2},
      Vector{0, -SATURN_AFELIO_SPEED}, 1.5 * SUN_MASS);

  binaryStars->addBody(s1);
  binaryStars->addBody(s2);

  return binaryStars;
}

auto createCollapsingBinaryStars(sf::RenderWindow& window) {
  auto collapsingBinaryStars = std::make_shared<Configuration>(
      "Collapsing Binary Stars", 2000, 1000000, window);

  std::unique_ptr<Body> s1 =
      std::make_unique<Star>(Vector{850, 400}, Vector{0, 20}, 50E14);
  std::unique_ptr<Body> s2 =
      std::make_unique<Star>(Vector{1150, 400}, Vector{0, -20}, 50E14);

  collapsingBinaryStars->addBody(s1);
  collapsingBinaryStars->addBody(s2);

  return collapsingBinaryStars;
}

auto createSolarSystemWithBlackHole(sf::RenderWindow& window) {
  auto solarSystemTillMars = std::make_shared<Configuration>(
      "Solar System with Black Hole", 3 * MARS_AFELIO, 1000000, window);

  auto height = 3 * MARS_AFELIO;

  std::unique_ptr<Body> sun = std::make_unique<Star>(
      Vector{height / 2, height / 2}, Vector{0, 0}, 3.3f * SUN_MASS);
  // THe smallest black hole is just 3.3 times the mass of the sun.
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

  solarSystemTillMars->addBody(sun);
  solarSystemTillMars->addBody(earth);
  solarSystemTillMars->addBody(mercury);
  solarSystemTillMars->addBody(venus);
  solarSystemTillMars->addBody(mars);
  solarSystemTillMars->addBody(moon);

  return solarSystemTillMars;
}

std::vector<std::shared_ptr<Configuration>> getConfigurations(
    sf::RenderWindow& window) {
  std::vector<std::shared_ptr<Configuration>> list;

  list.push_back(createSolarSystemTillMars(window));
  list.push_back(createSolarSystem(window));
  list.push_back(createEarthAndSun(window));
  list.push_back(createSolarSystemWithBlackHole(window));
  //   list.push_back(createThreeBodies(window));
  list.push_back(createBinaryStars(window));
  //   list.push_back(createCollapsingBinaryStars(window));

  return list;
}

};  // namespace gs
#endif