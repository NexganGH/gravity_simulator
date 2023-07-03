#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <vector>

#include "body.hpp"
#include "configuration.hpp"
#include "renderer.hpp"
#include "SFML/Graphics.hpp"

const float EARTH_SUN_DISTANCE = 149597870700;
const float EARTH_SPEED = 30.24E3;
const float EARTH_MASS = 5.9722E24;
const float SUN_MASS = 1.98855E30;

const float MERCURY_AFELIO=69.8E9;
const float MERCURY_AFELIO_SPEED=39.0E3;
const float MERCURY_MASS= 0.055*EARTH_MASS;

const float MOON_AFELIO=405500E3;
const float MOON_AFELIO_SPEED=0.970E3;
const float MOON_MASS= 7.3476E22;

const float VENUS_AFELIO=109.8E9;
const float VENUS_AFELIO_SPEED=34.78E3;
const float VENUS_MASS= 0.815*EARTH_MASS;

const float MARS_AFELIO=249.261E9;
const float MARS_AFELIO_SPEED=21.97E3;
const float MARS_MASS= 0.1*EARTH_MASS;

const float JUPITER_AFELIO=816.363E9;
const float JUPITER_AFELIO_SPEED=12.44E3;
const float JUPITER_MASS= 318*EARTH_MASS;

const float NEPTUNE_AFELIO=30.34*EARTH_SUN_DISTANCE;
const float NEPTUNE_AFELIO_SPEED=5.37E3;
const float NEPTUNE_MASS= 17*EARTH_MASS;


std::vector<std::shared_ptr<Configuration>> getConfigurations(sf::RenderWindow& window) {
  std::vector<std::shared_ptr<Configuration>> list;


  // Creating earth and sun
  auto earthAndSun = new Configuration("Earth & Sun", 2 * MARS_AFELIO + MARS_AFELIO, 1000000, window);
  //auto height = renderer.getUniverseHeight();

  auto height = 2*MARS_AFELIO  + EARTH_SUN_DISTANCE;//

  std::unique_ptr<Body> sun = std::make_unique<Planet>(
      Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2,
             height / 2},
      Vector{0, 0}, SUN_MASS);
  std::unique_ptr<Body> earth = std::make_unique<Planet>(
      Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2+EARTH_SUN_DISTANCE,
             height / 2},
      Vector{0, -EARTH_SPEED}, EARTH_MASS);
  std::unique_ptr<Body> mercury = std::make_unique<Planet>(
      Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2- MERCURY_AFELIO,
             height / 2},
      Vector{0, MERCURY_AFELIO_SPEED}, MERCURY_MASS);
  std::unique_ptr<Body> venus = std::make_unique<Planet>(
      Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2- VENUS_AFELIO,
             height / 2},
      Vector{0, VENUS_AFELIO_SPEED}, VENUS_MASS);
      std::unique_ptr<Body> mars = std::make_unique<Planet>(
      Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2- MARS_AFELIO,
             height / 2},
      Vector{0, MARS_AFELIO_SPEED}, MARS_MASS);


  std::unique_ptr<Body> moon = std::make_unique<Planet>(
      Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2+EARTH_SUN_DISTANCE+MOON_AFELIO,
             height / 2},
      Vector{0, -MOON_AFELIO_SPEED-EARTH_SPEED}, MOON_MASS);
  // std::unique_ptr<Body> jupiter = std::make_unique<Planet>(
  //     Vector{0.5 * 1E5 + JUPITER_AFELIO + JUPITER_AFELIO / 2- JUPITER_AFELIO,
  //            height / 2},
  //     Vector{0, JUPITER_AFELIO_SPEED}, JUPITER_MASS);
  // std::unique_ptr<Body> neptune = std::make_unique<Planet>(
  //     Vector{0.5 * 1E5 + NEPTUNE_AFELIO + NEPTUNE_AFELIO / 2- NEPTUNE_AFELIO,
  //            height / 2},
  //     Vector{0, NEPTUNE_AFELIO_SPEED}, NEPTUNE_MASS);
  

  earthAndSun->addBody(sun);
  earthAndSun->addBody(earth);
  earthAndSun->addBody(mercury);
  earthAndSun->addBody(venus);
  earthAndSun->addBody(mars);
  earthAndSun->addBody(moon);
  //added
//   earthAndSun->addBody(moon);

  //earthAndSun->addBody(neptune);

  list.push_back(std::unique_ptr<Configuration>(earthAndSun));
  

  // Add other configurations

  return list;
}








// std::unique_ptr<Renderer> earthAndSun(std::vector<std::unique_ptr<Body>>& bodies,
//                      sf::RenderWindow& window) {

//   auto renderer = Renderer::fromUniverseWidth(
//       window, 2 * EARTH_SUN_DISTANCE + EARTH_SUN_DISTANCE);

//   auto height = renderer->getUniverseHeight();

//   std::unique_ptr<Body> sun = std::make_unique<Planet>(
//       Vector{0.5 * 1E5 + EARTH_SUN_DISTANCE + EARTH_SUN_DISTANCE / 2,
//              height / 2},
//       Vector{0, 0}, 3.3 * SUN_MASS);
//   std::unique_ptr<Body> earth = std::make_unique<Planet>(
//       Vector{0.5 * 1E5 + EARTH_SUN_DISTANCE * 2 + EARTH_SUN_DISTANCE / 2,
//              height / 2},
//       Vector{0, -EARTH_SPEED}, EARTH_MASS);

//   bodies.push_back(std::move(sun));
//   bodies.push_back(std::move(earth));

//   return renderer;
// }

// std::unique_ptr<Renderer> starCollision(std::vector<std::unique_ptr<Body>>& bodies,
//                        sf::RenderWindow& window) {
//   const float EARTH_SUN_DISTANCE = 149597870700;
//   const float EARTH_SPEED = 30.24E3;
//   const float EARTH_MASS = 5.9722E24;
//   const float SUN_MASS = 1.98855E30;

//   auto renderer = Renderer::fromUniverseWidth(
//       window, 2 * EARTH_SUN_DISTANCE + EARTH_SUN_DISTANCE);

//   auto height = renderer->getUniverseHeight();

//   std::unique_ptr<Body> sun = std::make_unique<Planet>(
//       Vector{0.5 * 1E5 + EARTH_SUN_DISTANCE + EARTH_SUN_DISTANCE / 2,
//              height / 2},
//       Vector{0, 0}, SUN_MASS);
//   std::unique_ptr<Body> earth = std::make_unique<Planet>(
//       Vector{0.5 * 1E5 + EARTH_SUN_DISTANCE * 2 + EARTH_SUN_DISTANCE / 2,
//              height / 2},
//       Vector{0, -EARTH_SPEED}, EARTH_MASS);
//   std::unique_ptr<Body> star = std::make_unique<Planet>(
//       Vector{0.5 * 1E5 + EARTH_SUN_DISTANCE + EARTH_SUN_DISTANCE,
//              height / 2 + height / 4},
//       Vector{0, -EARTH_SPEED * 2}, 5E30);

//   bodies.push_back(std::move(sun));
//   bodies.push_back(std::move(earth));
//   bodies.push_back(std::move(star));

//   return renderer;
// }

// void stableOrbitTwoPlanets(std::vector<std::unique_ptr<Body>>& bodies) {
//   std::unique_ptr<Body> p1 =
//       std::make_unique<Planet>(Vector{800, 400} * 100, Vector{0, 0}, 10E15);
//   std::unique_ptr<Body> p2 =
//       std::make_unique<Planet>(Vector{500, 400} * 100, Vector{0, 45}, 10E13);

//   bodies.push_back(std::move(p1));
//   bodies.push_back(std::move(p2));
// }

// void stableOrbitTwoPlanets2(std::vector<std::unique_ptr<Body>>& bodies) {
//   std::unique_ptr<Body> p1 =
//       std::make_unique<Planet>(Vector{800, 400} * 100, Vector{0, 0}, 10E16);
//   std::unique_ptr<Body> p2 =
//       std::make_unique<Planet>(Vector{800, 100} * 100, Vector{-180, 0}, 10E11);

//   bodies.push_back(std::move(p1));
//   bodies.push_back(std::move(p2));
// }

// void threeBodies(std::vector<std::unique_ptr<Body>>& bodies) {
//   std::unique_ptr<Body> p2 =
//       std::make_unique<Planet>(Vector{500, 400}, Vector{0, 30}, 10E14);
//   std::unique_ptr<Body> p1 =
//       std::make_unique<Planet>(Vector{800, 400}, Vector{0, 0}, 50E14);

//   std::unique_ptr<Body> p3 =
//       std::make_unique<Planet>(Vector{1000, 500}, Vector{10, 30}, 10E14);

//   bodies.push_back(std::move(p1));
//   bodies.push_back(std::move(p2));
//   bodies.push_back(std::move(p3));
// }

// void binaryStars(std::vector<std::unique_ptr<Body>>& bodies) {
//   std::unique_ptr<Body> p1 =
//       std::make_unique<Planet>(Vector{575, 400}, Vector{0, 25}, 20E14);
//   std::unique_ptr<Body> p2 =
//       std::make_unique<Planet>(Vector{700, 400}, Vector{0, -25}, 20E14);

//   bodies.push_back(std::move(p1));
//   bodies.push_back(std::move(p2));
// }

// void collapsingBinaryStars(std::vector<std::unique_ptr<Body>>& bodies) {
//   std::unique_ptr<Body> p1 =
//       std::make_unique<Planet>(Vector{500, 400}, Vector{0, 20}, 50E14);
//   std::unique_ptr<Body> p2 =
//       std::make_unique<Planet>(Vector{800, 400}, Vector{0, -20}, 50E14);

//   bodies.push_back(std::move(p1));
//   bodies.push_back(std::move(p2));
// }




//TERRA LUNA RELATIVISTICHE
// std::vector<std::shared_ptr<Configuration>> getConfigurations() {
//   std::vector<std::shared_ptr<Configuration>> list;


//   // Creating earth and sun
//   auto earthAndSun = new Configuration("Earth & Sun", 2 * MOON_AFELIO + MOON_AFELIO, 50);
//   //auto height = renderer.getUniverseHeight();

//   auto height = 2*MOON_AFELIO  + MOON_AFELIO;//

 
//   std::unique_ptr<Body> earth = std::make_unique<Planet>(
//       Vector{0.5 * 1E5 + MOON_AFELIO + MOON_AFELIO / 2,
//              height / 2},
//       Vector{0, 0}, EARTH_MASS);
  


//   std::unique_ptr<Body> moon = std::make_unique<Planet>(
//       Vector{0.5 * 1E5 + MOON_AFELIO + MOON_AFELIO / 2+MOON_AFELIO,
//              height / 2},
//       Vector{0, -MOON_AFELIO_SPEED}, MOON_MASS);
  
  

  
//   earthAndSun->addBody(earth);
  
//   earthAndSun->addBody(moon);

//   //earthAndSun->addBody(neptune);

//   list.push_back(std::unique_ptr<Configuration>(earthAndSun));
  

  

//   return list;
// }

#endif