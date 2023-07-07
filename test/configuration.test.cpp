#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "configuration.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

#include "doctest.h"

TEST_CASE("Testing configuration function") {
  SUBCASE("Testing addBody() and createBodies()") {
    sf::RenderWindow window;
    gs::Configuration conf("test configuration", 10, 10, window);
    std::unique_ptr<gs::Body> p1 =
        std::make_unique<gs::Planet>(gs::Vector{0, 0}, gs::Vector{0, 0}, 1);
    std::unique_ptr<gs::Body> p2 =
        std::make_unique<gs::Planet>(gs::Vector{1, 1}, gs::Vector{1, 1}, 1);
    std::unique_ptr<gs::Body> p3 =
        std::make_unique<gs::Planet>(gs::Vector{2, 2}, gs::Vector{-1, -1}, 1);

    conf.addBody(p1);
    conf.addBody(p2);
    conf.addBody(p3);

    std::vector<std::unique_ptr<gs::Body>> bodies = conf.createBodies();

    CHECK(bodies[0]->getPosition() == gs::Vector{0, 0});
    CHECK(bodies[0]->getVelocity() == gs::Vector{0, 0});
    CHECK(bodies[0]->getMass() == 1);

    CHECK(bodies[1]->getPosition() == gs::Vector{1, 1});
    CHECK(bodies[1]->getVelocity() == gs::Vector{1, 1});
    CHECK(bodies[1]->getMass() == 1);

    CHECK(bodies[2]->getPosition() == gs::Vector{2, 2});
    CHECK(bodies[2]->getVelocity() == gs::Vector{-1, -1});
    CHECK(bodies[2]->getMass() == 1);
  }

  SUBCASE("Testing createPhysicsEngine function") {
    sf::RenderWindow window;
    gs::Configuration conf("test configuration", 10, 10, window);
    std::unique_ptr<gs::PhysicsEngine> ph = conf.createPhysicsEngine();
    CHECK(ph->getTimeScale() == 10);
  }
}