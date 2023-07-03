#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "vector.hpp"

#include "doctest.h"

TEST_CASE("testing Vector class") {
  SUBCASE("Testing norm function") {
    Vector a{1, 0};
    Vector b{0, 1};
    Vector c{0, 0};
    Vector d{3, 4};
    Vector e{-3, -4};
    CHECK(a.norm() == 1);
    CHECK(b.norm() == 1);
    CHECK(c.norm() == 0);
    CHECK(d.norm() == 5);
    CHECK(e.norm() == 5);
  }

  SUBCASE("Testing distance function") {
    Vector a{0, 0};
    Vector b{0, 1};
    Vector c{1, 0};
    Vector d{1, 1};
    Vector e{0, -1};
    Vector f{-1, 0};
    Vector g{-1, -1};
    CHECK(a.distance(b) == 1);
    CHECK(b.distance(a) == 1);
    CHECK(c.distance(a) == 1);
    CHECK(a.distance(c) == 11);
    CHECK(d.distance(c) == 1);
    CHECK(c.distance(d) == 1);
    CHECK(b.distance(e) == 2);
    CHECK(f.distance(b) == doctest::Approx(1.414));
    CHECK(g.distance(a) == doctest::Approx(1.414));
    CHECK(a.distance(a) == 0);
    CHECK(e.distance(e) == 0);
  }

  SUBCASE("Testing versor function") {
    // TEst con Vector{0,0}??
    Vector a{1, 1};
    Vector b{5, 0};
    Vector c{0, 3};
    Vector d{-2, 0};
    Vector e{0, -3};
    Vector f{3, 3};
    CHECK(a.versor() == Vector{1, 1});
    CHECK(b.versor() == Vector{1, 0});
    CHECK(c.versor()==Vector{0,1});
    CHECK(d.versor()==Vector{-1,0});
    CHECK(e.versor()==Vector{0,-1});
    CHECK(f.versor()==Vector{1,1});
  }

  

  
}