#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "simulation_state.hpp"

#include <SFML/Graphics.hpp>

#include "body.hpp"
#include "configurations.hpp"
#include "constants.hpp"
#include "doctest.h"

TEST_CASE("Testing simulationState class") {
  // getRenderer can't be tested
  SUBCASE("testing getBodies and getPhysicsEngine function") {
    auto height = 3 * gs::MARS_AFELIO;

    sf::RenderWindow window;
    auto conf = gs::getConfigurations(window);
    auto firstConfiguration = conf[0];
    gs::SimulationState simulation_state(firstConfiguration);

    auto& bodies = simulation_state.getBodies();

    CHECK(bodies[0]->getMass() == gs::SUN_MASS);
    CHECK(bodies[1]->getMass() == gs::EARTH_MASS);
    CHECK(bodies[2]->getMass() == gs::MERCURY_MASS);
    CHECK(bodies[3]->getMass() == gs::VENUS_MASS);
    CHECK(bodies[4]->getMass() == gs::MARS_MASS);
    CHECK(bodies[5]->getMass() == gs::MOON_MASS);

    CHECK(bodies[0]->getPosition() == gs::Vector{height / 2, height / 2});
    CHECK(bodies[1]->getPosition() ==
          gs::Vector{height / 2 + gs::EARTH_SUN_DISTANCE, height / 2});
    CHECK(bodies[2]->getPosition() ==
          gs::Vector{height / 2 - gs::MERCURY_AFELIO, height / 2});
    CHECK(bodies[3]->getPosition() ==
          gs::Vector{height / 2 - gs::VENUS_AFELIO, height / 2});
    CHECK(bodies[4]->getPosition() ==
          gs::Vector{height / 2 - gs::MARS_AFELIO, height / 2});
    CHECK(bodies[5]->getPosition() ==
          gs::Vector{height / 2 + gs::EARTH_SUN_DISTANCE + gs::MOON_AFELIO,
                     height / 2});

    CHECK(bodies[0]->getVelocity() == gs::Vector{0, 0});
    CHECK(bodies[1]->getVelocity() == gs::Vector{0, -gs::EARTH_SPEED});
    CHECK(bodies[2]->getVelocity() == gs::Vector{0, gs::MERCURY_AFELIO_SPEED});
    CHECK(bodies[3]->getVelocity() == gs::Vector{0, gs::VENUS_AFELIO_SPEED});
    CHECK(bodies[4]->getVelocity() == gs::Vector{0, gs::MARS_AFELIO_SPEED});
    CHECK(bodies[5]->getVelocity() ==
          gs::Vector{0, -gs::MOON_AFELIO_SPEED - gs::EARTH_SPEED});
    // getPhysicsEngine

    auto& ph = simulation_state.getPhysicsEngine();
    CHECK(ph->getTimeScale() ==
          1000000);  // remember to change if the value of timescale is changed
                     // in configurations
    CHECK(ph->getRealSecondsElapsed() == 0);
    CHECK(ph->getSimulationSecondsElapsed() == 0);
  }

  SUBCASE("testing reset function in the only case we can") {
    sf::RenderWindow window;
    auto conf = gs::getConfigurations(window);
    auto firstConfiguration = conf[0];
    gs::SimulationState simulation_state(firstConfiguration);

    gs::PhysicsEngine ph(1000);
    ph.toggleRunning();
    ph.evolve(simulation_state.getBodies(), 1000);

    simulation_state.reset();

    auto& bodies = simulation_state.getBodies();

    CHECK(bodies[0]->getMass() == gs::SUN_MASS);
    CHECK(bodies[1]->getMass() == gs::EARTH_MASS);
    CHECK(bodies[2]->getMass() == gs::MERCURY_MASS);
    CHECK(bodies[3]->getMass() == gs::VENUS_MASS);
    CHECK(bodies[4]->getMass() == gs::MARS_MASS);
    CHECK(bodies[5]->getMass() == gs::MOON_MASS);

    auto height = 3 * gs::MARS_AFELIO;

    CHECK(bodies[0]->getPosition() == gs::Vector{height / 2, height / 2});
    CHECK(bodies[1]->getPosition() ==
          gs::Vector{height / 2 + gs::EARTH_SUN_DISTANCE, height / 2});
    CHECK(bodies[2]->getPosition() ==
          gs::Vector{height / 2 - gs::MERCURY_AFELIO, height / 2});
    CHECK(bodies[3]->getPosition() ==
          gs::Vector{height / 2 - gs::VENUS_AFELIO, height / 2});
    CHECK(bodies[4]->getPosition() ==
          gs::Vector{height / 2 - gs::MARS_AFELIO, height / 2});
    CHECK(bodies[5]->getPosition() ==
          gs::Vector{height / 2 + gs::EARTH_SUN_DISTANCE + gs::MOON_AFELIO,
                     height / 2});

    CHECK(bodies[0]->getVelocity() == gs::Vector{0, 0});
    CHECK(bodies[1]->getVelocity() == gs::Vector{0, -gs::EARTH_SPEED});
    CHECK(bodies[2]->getVelocity() == gs::Vector{0, gs::MERCURY_AFELIO_SPEED});
    CHECK(bodies[3]->getVelocity() == gs::Vector{0, gs::VENUS_AFELIO_SPEED});
    CHECK(bodies[4]->getVelocity() == gs::Vector{0, gs::MARS_AFELIO_SPEED});
    CHECK(bodies[5]->getVelocity() ==
          gs::Vector{0, -gs::MOON_AFELIO_SPEED - gs::EARTH_SPEED});
    // getPhysicsEngine

    auto& phh = simulation_state.getPhysicsEngine();
    CHECK(phh->getTimeScale() ==
          1000000);  // remember to change if the value of timescale is changed
                     // in configurations
    CHECK(phh->getRealSecondsElapsed() == 0);
    CHECK(phh->getSimulationSecondsElapsed() == 0);
  }
}