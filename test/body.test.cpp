#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "body.hpp"

#include "doctest.h"
#include "vector.hpp"

TEST_CASE("testing Body class") {
  Planet p1(Vector{0, 0}, Vector{0, 0}, 1);
  Planet p2(Vector{1, 1}, Vector{1, 1}, 2);
  Planet p3(Vector{1, -1}, Vector{-1, 1}, 0);
  SUBCASE("Testing getMass function") {
    CHECK(p1.getMass() == 1);
    CHECK(p2.getMass() == 2);
    CHECK_THROWS(p3.getMass());
  }
  SUBCASE("Testing getPosition function") {
    CHECK(p1.getPosition() == Vector a{0, 0});
    CHECK(p2.getPosition() == Vector b{1, 1});
    CHECK(p3.getPosition() == Vector c{1, -1});
  }
}
