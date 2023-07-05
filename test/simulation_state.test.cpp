#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "simulation_state.hpp"

#include <SFML/Graphics.hpp>

#include "body.hpp"
#include "configurations.hpp"
#include "doctest.h"

TEST_CASE("Testing simulationState class") {
  // non si può testare getRenderer
  SUBCASE("testing getBodies and getPhysicsEngine function") {
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
    auto height = 2 * MARS_AFELIO + EARTH_SUN_DISTANCE;

    sf::RenderWindow window;
    auto conf = getConfigurations(window);
    auto firstConfiguration = conf[0];
    SimulationState simulation_state(firstConfiguration);

    auto& bodies = simulation_state.getBodies();

    CHECK(bodies[0]->getMass() == SUN_MASS);
    CHECK(bodies[1]->getMass() == EARTH_MASS);
    CHECK(bodies[2]->getMass() == MERCURY_MASS);
    CHECK(bodies[3]->getMass() == VENUS_MASS);
    CHECK(bodies[4]->getMass() == MARS_MASS);
    CHECK(bodies[5]->getMass() == MOON_MASS);

    CHECK(bodies[0]->getPosition() ==
          Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2, height / 2});
    CHECK(bodies[1]->getPosition() ==
          Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2 + EARTH_SUN_DISTANCE,
                 height / 2});
    CHECK(bodies[2]->getPosition() ==
          Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2 - MERCURY_AFELIO,
                 height / 2});
    CHECK(bodies[3]->getPosition() ==
          Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2 - VENUS_AFELIO,
                 height / 2});
    CHECK(bodies[4]->getPosition() ==
          Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2 - MARS_AFELIO,
                 height / 2});
    CHECK(bodies[5]->getPosition() ==
          Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2 +
                     EARTH_SUN_DISTANCE + MOON_AFELIO,
                 height / 2});

    CHECK(bodies[0]->getVelocity() == Vector{0, 0});
    CHECK(bodies[1]->getVelocity() == Vector{0, -EARTH_SPEED});
    CHECK(bodies[2]->getVelocity() == Vector{0, MERCURY_AFELIO_SPEED});
    CHECK(bodies[3]->getVelocity() == Vector{0, VENUS_AFELIO_SPEED});
    CHECK(bodies[4]->getVelocity() == Vector{0, MARS_AFELIO_SPEED});
    CHECK(bodies[5]->getVelocity() ==
          Vector{0, -MOON_AFELIO_SPEED - EARTH_SPEED});
    // getPhysicsEngine

    auto& ph = simulation_state.getPhysicsEngine();
    CHECK(ph->getTimeScale() ==
          1000000);  // cambiare se si cambia il timescale in configurations
    CHECK(ph->getRealSecondsElapsed() == 0);
    CHECK(ph->getSimulationSecondsElapsed() == 0);
  }

  SUBCASE("testing reset function in the only case we can") {
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
    auto height = 2 * MARS_AFELIO + EARTH_SUN_DISTANCE;

    sf::RenderWindow window;
    auto conf = getConfigurations(window);
    auto firstConfiguration = conf[0];
    SimulationState simulation_state(firstConfiguration);

    auto& bodies = simulation_state.getBodies();

    // chiamo reset anche se non si è modificata la configurazione iniziale,
    // testiamo quindi se reset lascia invariata la configurazione
    simulation_state.reset();

    CHECK(bodies[0]->getMass() == SUN_MASS);
    CHECK(bodies[1]->getMass() == EARTH_MASS);
    CHECK(bodies[2]->getMass() == MERCURY_MASS);
    CHECK(bodies[3]->getMass() == VENUS_MASS);
    CHECK(bodies[4]->getMass() == MARS_MASS);
    CHECK(bodies[5]->getMass() == MOON_MASS);

    CHECK(bodies[0]->getPosition() ==
          Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2, height / 2});
    CHECK(bodies[1]->getPosition() ==
          Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2 + EARTH_SUN_DISTANCE,
                 height / 2});
    CHECK(bodies[2]->getPosition() ==
          Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2 - MERCURY_AFELIO,
                 height / 2});
    CHECK(bodies[3]->getPosition() ==
          Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2 - VENUS_AFELIO,
                 height / 2});
    CHECK(bodies[4]->getPosition() ==
          Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2 - MARS_AFELIO,
                 height / 2});
    CHECK(bodies[5]->getPosition() ==
          Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2 +
                     EARTH_SUN_DISTANCE + MOON_AFELIO,
                 height / 2});

    CHECK(bodies[0]->getVelocity() == Vector{0, 0});
    CHECK(bodies[1]->getVelocity() == Vector{0, -EARTH_SPEED});
    CHECK(bodies[2]->getVelocity() == Vector{0, MERCURY_AFELIO_SPEED});
    CHECK(bodies[3]->getVelocity() == Vector{0, VENUS_AFELIO_SPEED});
    CHECK(bodies[4]->getVelocity() == Vector{0, MARS_AFELIO_SPEED});
    CHECK(bodies[5]->getVelocity() ==
          Vector{0, -MOON_AFELIO_SPEED - EARTH_SPEED});
    // getPhysicsEngine

    auto& ph = simulation_state.getPhysicsEngine();
    CHECK(ph->getTimeScale() ==
          1000000);  // cambiare se si cambia il timescale in configurations
    CHECK(ph->getRealSecondsElapsed() == 0);
    CHECK(ph->getSimulationSecondsElapsed() == 0);
  }
}