#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "physics_engine.hpp"

#include <SFML/Graphics.hpp>

#include "body.hpp"
#include "vector.hpp"
#include "doctest.h"

TEST_CASE("Testing PhysicsEngine class") {
  SUBCASE("Testing getTimeScale function an the constructor") {
    PhysicsEngine ph(1);
    PhysicsEngine a(-11);
    PhysicsEngine b(0);
    PhysicsEngine c(2);
    PhysicsEngine d(0.1);

    CHECK(ph.getTimeScale() == 1);
    CHECK_THROWS(a.getTimeScale());
    CHECK_THROWS(b.getTimeScale());
    CHECK(c.getTimeScale() == 2);
    CHECK(d.getTimeScale() == 0.1);
  }

  SUBCASE("Testing setTimeScale function") {
    PhysicsEngine ph(1);
    PhysicsEngine a(1);
    PhysicsEngine b(1);
    PhysicsEngine c(1);
    PhysicsEngine d(1);

    ph.setTimeScale(1);
    a.setTimeScale(0);
    b.setTimeScale(2);
    c.setTimeScale(-1);
    d.setTimeScale(0.5);

    CHECK(ph.getTimeScale() == 1);
    CHECK_THROWS(a.getTimeScale());
    CHECK(b.getTimeScale() == 2);
    CHECK_THROWS(c.getTimeScale());
    CHECK(d.getTimeScale() == 0.5);
  }

  SUBCASE("Testing isRunning and toggleRunning functions") {
    PhysicsEngine ph(1);
    CHECK(ph.isRunning() == false);
    ph.toggleRunning();
    CHECK(ph.isRunning() == true);
    ph.toggleRunning();
    CHECK(ph.isRunning() == false);
    ph.toggleRunning();
    ph.toggleRunning();
    CHECK(ph.isRunning() == false);
  }

  // these three functions will be checked further as well in next subcases
  SUBCASE(
      "Testing getSimulationSecondsElapsed and getRealSecondsElapsed and "
      "resetTimeElapsed in one only case") {
    PhysicsEngine ph(1);
    CHECK(ph.getSimulationSecondsElapsed() == 0);
    CHECK(ph.getRealSecondsElapsed() == 0);
    ph.resetTimeElapsed();
    CHECK(ph.getSimulationSecondsElapsed() == 0);
    CHECK(ph.getRealSecondsElapsed() == 0);
  }

  SUBCASE("Testing evolve function with _running field set to flase") {
    std::unique_ptr<Body> p1 =
        std::make_unique<Planet>(Vector{0, 0}, Vector{0, 0}, 1);
    std::unique_ptr<Body> p2 =
        std::make_unique<Planet>(Vector{0, 1}, Vector{0, 0}, 1);

    // prima di applicare la gravità ai corpi mi aspetto che le accelerazioni
    // dei corpi siano nulle
    CHECK(p1->getAcceleration() == Vector{0, 0});
    CHECK(p2->getAcceleration() == Vector{0, 0});

    std::vector<std::unique_ptr<Body>> bodies;
    bodies.push_back(std::move(p1));
    bodies.push_back(std::move(p2));

    PhysicsEngine ph(1);

    double dt = 1;

    ph.evolve(bodies, dt);

    // poichè la varibaile _running è su false il dt usato per calcolare le
    // nuove posizioni e velocità sarà nullo per cui l'effetto che si ottiene è
    // quello di non aver applicato alcuna forza.

    CHECK(bodies[0]->getPosition() == Vector{0, 0});
    CHECK(bodies[1]->getPosition() == Vector{0, 1});
    CHECK(bodies[0]->getVelocity() == Vector{0, 0});
    CHECK(bodies[0]->getVelocity() == Vector{0, 0});

    CHECK(ph.getRealSecondsElapsed() ==
          (ph.getSimulationSecondsElapsed()) / ph.getTimeScale());
    // tesstiamo di nuovo la funzione resetTimeElapsed
    ph.resetTimeElapsed();
    CHECK(ph.getSimulationSecondsElapsed() == 0);
    CHECK(ph.getRealSecondsElapsed() == 0);
  }

  SUBCASE("Testing evolve function with _running field set to true") {
    std::unique_ptr<Body> p1 =
        std::make_unique<Planet>(Vector{0, 0}, Vector{0, 0}, 1);
    std::unique_ptr<Body> p2 =
        std::make_unique<Planet>(Vector{0, 1}, Vector{0, 0}, 1);

    // prima di applicare la gravità ai corpi mi aspetto che le accelerazioni
    // dei corpi siano nulle
    CHECK(p1->getAcceleration() == Vector{0, 0});
    CHECK(p2->getAcceleration() == Vector{0, 0});

    std::vector<std::unique_ptr<Body>> bodies;
    bodies.push_back(std::move(p1));
    bodies.push_back(std::move(p2));

    PhysicsEngine ph(1);

    double dt = 1;

    // sposto ora la variabile isRunning su true e verifico che si sia spostata
    // anche se la funzione toggle running dovrebbe essera ffidabile in quanto
    // precedentemente testata
    ph.toggleRunning();
    CHECK(ph.isRunning()==true);

    ph.evolve(bodies, dt);

    
//calcola i nuovi valori // todo 
    CHECK(bodies[0]->getPosition() == Vector{0, 0});
    CHECK(bodies[1]->getPosition() == Vector{0, 1});
    CHECK(bodies[0]->getVelocity() == Vector{0, 0});
    CHECK(bodies[0]->getVelocity() == Vector{0, 0});

    CHECK(ph.getRealSecondsElapsed() ==doctest::Approx(
          (ph.getSimulationSecondsElapsed()) / ph.getTimeScale()).epsilon(0.001));
    // tesstiamo di nuovo la funzione resetTimeElapsed
    ph.resetTimeElapsed();
    CHECK(ph.getSimulationSecondsElapsed() == 0);
    CHECK(ph.getRealSecondsElapsed() == 0);
  }

  //testa se il vettore è vuoto
  //testa se il vettore è pieno di puntatori nulli
  //testa se il dt che passo aevolve è minore di zero 
}