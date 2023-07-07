#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "body.hpp"

#include <SFML/Graphics.hpp>

#include "doctest.h"

TEST_CASE("testing Body class") {
  gs::Planet p1(gs::Vector{0, 0}, gs::Vector{0, 0}, 1);
  gs::Planet p2(gs::Vector{1, 1}, gs::Vector{1, 1}, 2);
  gs::Planet p3(gs::Vector{1, -1}, gs::Vector{-1, 1}, 1);

  SUBCASE("Testing getMass function") {
    CHECK(p1.getMass() == 1);
    CHECK(p2.getMass() == 2);
    CHECK_THROWS(gs::Planet(gs::Vector{1, -1}, gs::Vector{-1, 1}, 0));
  }

  SUBCASE("Testing getPosition function") {
    CHECK(p1.getPosition() == gs::Vector{0, 0});
    CHECK(p2.getPosition() == gs::Vector{1, 1});
    CHECK(p3.getPosition() == gs::Vector{1, -1});
  }

  SUBCASE("Testing getVelocity function") {
    CHECK(p1.getVelocity() == gs::Vector{0, 0});
    CHECK(p2.getVelocity() == gs::Vector{1, 1});
    CHECK(p3.getVelocity() == gs::Vector{-1, 1});
  }

  SUBCASE("Testing getAcceleration function") {
    CHECK(p1.getAcceleration() == gs::Vector{0, 0});
    CHECK(p2.getAcceleration() == gs::Vector{0, 0});
    CHECK(p3.getAcceleration() == gs::Vector{0, 0});
  }

  SUBCASE("Testing setPosition function") {
    p1.setPosition({1, 0});
    p2.setPosition({0, 1});
    p3.setPosition({-1, -1});
    CHECK(p1.getPosition() == gs::Vector{1, 0});
    CHECK(p2.getPosition() == gs::Vector{0, 1});
    CHECK(p3.getPosition() == gs::Vector{-1, -1});
  }

  SUBCASE("Testing setVelocity function") {
    p1.setVelocity({-1, 1});
    p2.setVelocity({0, 0});
    p3.setVelocity({2, 0});
    CHECK(p1.getVelocity() == gs::Vector{-1, 1});
    CHECK(p2.getVelocity() == gs::Vector{0, 0});
    CHECK(p3.getVelocity() == gs::Vector{2, 0});
  }

  SUBCASE("Testing the addForce function") {
    p1.addForce({1, 1});
    p2.addForce({0, 0});
    CHECK(p1.getAcceleration() == gs::Vector{1, 1});
    CHECK(p2.getAcceleration() == gs::Vector{0, 0});
    p1.addForce({-1, -1});
    p2.addForce({2, 2});
    CHECK(p1.getAcceleration() == gs::Vector{0, 0});
    CHECK(p2.getAcceleration() == gs::Vector{1, 1});
  }

  SUBCASE("Testing resetForce function") {
    p1.addForce({1, 1});
    p1.addForce({2, 1});
    p2.addForce({1, -1});
    p1.addForce({-1, 3});
    p1.resetForce();
    p2.resetForce();
    CHECK(p1.getAcceleration() == gs::Vector{0, 0});
    CHECK(p2.getAcceleration() == gs::Vector{0, 0});
  }

  SUBCASE("testing getShape function") {
    double firstScale = 0;
    double secondScale = 1;
    double thirdScale = -1;

    auto a = p1.getShape(secondScale);
    auto b = p2.getShape(secondScale);
    auto c = p3.getShape(secondScale);
    // testing first the assert
    CHECK_THROWS(p1.getShape(firstScale));
    CHECK_THROWS(p1.getShape(thirdScale));

    // testing if the shapes are set in the same position of the correspondant
    // planet
    CHECK(a->getPosition() == sf::Vector2f{0, 0});
    CHECK(b->getPosition() == sf::Vector2f{1, 1});
    CHECK(c->getPosition() == sf::Vector2f{1, -1});
  }

  SUBCASE("testing the clone function") {
    std::unique_ptr<gs::Body> a = p1.clone();
    std::unique_ptr<gs::Body> b = p2.clone();
    CHECK(a->getPosition() == p1.getPosition());
    CHECK(a->getVelocity() == p1.getVelocity());
    CHECK(a->getMass() == p1.getMass());
    CHECK(b->getPosition() == p2.getPosition());
    CHECK(b->getVelocity() == p2.getVelocity());
    CHECK(b->getMass() == p2.getMass());
  }
}

// Methods of class gs::Star are defined as the gs::Planet' ones, so it is like
// they had already been tested
