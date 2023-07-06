#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "physics_engine.hpp"

#include <SFML/Graphics.hpp>

#include "doctest.h"

TEST_CASE("Testing PhysicsEngine class") {
  SUBCASE("Testing getTimeScale() function an the constructor") {
    gs::PhysicsEngine ph(1);
    // PhysicsEngine a(-11);
    // PhysicsEngine b(0);
    gs::PhysicsEngine c(2);
    gs::PhysicsEngine d(0.1);

    CHECK(ph.getTimeScale() == 1);
    // CHECK_THROWS(PhysicsEngine(-11));
    //  CHECK_THROWS(b.getTimeScale());
    CHECK(c.getTimeScale() == 2);
    CHECK(d.getTimeScale() == 0.1);
  }

  SUBCASE("Testing setTimeScale function") {
    gs::PhysicsEngine ph(1);
    gs::PhysicsEngine a(1);
    gs::PhysicsEngine b(1);
    gs::PhysicsEngine c(1);
    gs::PhysicsEngine d(1);

    ph.setTimeScale(1);
    b.setTimeScale(2);

    d.setTimeScale(0.5);
    CHECK_THROWS(c.setTimeScale(-1));
    CHECK(ph.getTimeScale() == 1);
    CHECK(b.getTimeScale() == 2);
    CHECK(d.getTimeScale() == 0.5);
  }

  SUBCASE("Testing isRunning and toggleRunning functions") {
    gs::PhysicsEngine ph(1);
    CHECK(!ph.isRunning());
    ph.toggleRunning();
    CHECK(ph.isRunning());
    ph.toggleRunning();
    CHECK(!ph.isRunning());
    ph.toggleRunning();
    ph.toggleRunning();
    CHECK(!ph.isRunning());
  }

  // these three functions will be checked further as well in next subcases
  SUBCASE(
      "Testing getSimulationSecondsElapsed and getRealSecondsElapsed and "
      "resetTimeElapsed in one only case") {
    gs::PhysicsEngine ph(1);
    CHECK(ph.getSimulationSecondsElapsed() == 0);
    CHECK(ph.getRealSecondsElapsed() == 0);
  }

  SUBCASE("Testing evolve function with _running field set to flase") {
    std::unique_ptr<gs::Body> p1 =
        std::make_unique<gs::Planet>(gs::Vector{0, 0}, gs::Vector{0, 0}, 1);
    std::unique_ptr<gs::Body> p2 =
        std::make_unique<gs::Planet>(gs::Vector{0, 1}, gs::Vector{0, 0}, 1);

    // prima di applicare la gravità ai corpi mi aspetto che le accelerazioni
    // dei corpi siano nulle
    CHECK(p1->getAcceleration() == gs::Vector{0, 0});
    CHECK(p2->getAcceleration() == gs::Vector{0, 0});

    std::vector<std::unique_ptr<gs::Body>> bodies;
    bodies.push_back(std::move(p1));
    bodies.push_back(std::move(p2));

    gs::PhysicsEngine ph(1);

    double dt = 1;

    ph.evolve(bodies, dt);

    // poichè la varibaile _running è su false il dt usato per calcolare le
    // nuove posizioni e velocità sarà nullo per cui l'effetto che si ottiene è
    // quello di non aver applicato alcuna forza.

    CHECK(bodies[0]->getPosition() == gs::Vector{0, 0});
    CHECK(bodies[1]->getPosition() == gs::Vector{0, 1});
    CHECK(bodies[0]->getVelocity() == gs::Vector{0, 0});
    CHECK(bodies[0]->getVelocity() == gs::Vector{0, 0});

    CHECK(ph.getRealSecondsElapsed() ==
          (ph.getSimulationSecondsElapsed()) / ph.getTimeScale());
  }

  SUBCASE("Testing evolve function with running set to true") {
    std::unique_ptr<gs::Body> p1 =
        std::make_unique<gs::Planet>(gs::Vector{0, 0}, gs::Vector{0, 0}, 1);
    std::unique_ptr<gs::Body> p2 =
        std::make_unique<gs::Planet>(gs::Vector{0, 1}, gs::Vector{0, 0}, 1);

    // prima di applicare la gravità ai corpi mi aspetto che le accelerazioni
    // dei corpi siano nulle
    CHECK(p1->getAcceleration() == gs::Vector{0, 0});
    CHECK(p2->getAcceleration() == gs::Vector{0, 0});

    std::vector<std::unique_ptr<gs::Body>> bodies;
    bodies.push_back(std::move(p1));
    bodies.push_back(std::move(p2));

    gs::PhysicsEngine ph(1);

    double dt = 1;

    // sposto ora la variabile isRunning su true e verifico che si sia spostata
    // anche se la funzione toggle running dovrebbe essera ffidabile in quanto
    // precedentemente testata
    ph.toggleRunning();
    CHECK(ph.isRunning());

    ph.evolve(bodies, dt);

    // calcola i nuovi valori // todo
    // CHECK(bodies[0]->getPosition() == Vector{0, 0});
    // CHECK(bodies[1]->getPosition() == Vector{0, 1});
    // CHECK(bodies[0]->getVelocity() == Vector{0, 0});
    // CHECK(bodies[0]->getVelocity() == Vector{0, 0});

    CHECK(
        ph.getRealSecondsElapsed() ==
        doctest::Approx((ph.getSimulationSecondsElapsed()) / ph.getTimeScale())
            .epsilon(0.001));
  }
}