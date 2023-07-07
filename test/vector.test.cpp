#ifndef DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "vector.hpp"

#include "doctest.h"

TEST_CASE("testing Vector class") {
  SUBCASE("Testing norm function") {
    gs::Vector a{1, 0};
    gs::Vector b{0, 1};
    gs::Vector c{0, 0};
    gs::Vector d{3, 4};
    gs::Vector e{-3, -4};
    CHECK(a.norm() == 1);
    CHECK(b.norm() == 1);
    CHECK(c.norm() == 0);
    CHECK(d.norm() == 5);
    CHECK(e.norm() == 5);
  }

  SUBCASE("Testing distance function") {
    gs::Vector a{0, 0};
    gs::Vector b{0, 1};
    gs::Vector c{1, 0};
    gs::Vector d{1, 1};
    gs::Vector e{0, -1};
    gs::Vector f{-1, 0};
    gs::Vector g{-1, -1};
    CHECK(a.distance(b) == 1);
    CHECK(b.distance(a) == 1);
    CHECK(c.distance(a) == 1);
    CHECK(a.distance(c) == 1);
    CHECK(d.distance(c) == 1);
    CHECK(c.distance(d) == 1);
    CHECK(b.distance(e) == 2);
    CHECK(f.distance(b) == doctest::Approx(1.4142));
    CHECK(g.distance(a) == doctest::Approx(1.4142));
    CHECK(a.distance(a) == 0);
    CHECK(e.distance(e) == 0);
  }

  SUBCASE("Testing versor function") {
    gs::Vector a{1, 1};
    gs::Vector b{5, 0};
    gs::Vector c{0, 3};
    gs::Vector d{-2, 0};
    gs::Vector e{0, -3};
    gs::Vector f{3, 3};
    gs::Vector g{0, 0};
    CHECK((a.versor()).x == doctest::Approx(0.7071));
    CHECK((a.versor()).y == doctest::Approx(0.7071));
    CHECK(b.versor() == gs::Vector{1, 0});
    CHECK(c.versor() == gs::Vector{0, 1});
    CHECK(d.versor() == gs::Vector{-1, 0});
    CHECK(e.versor() == gs::Vector{0, -1});
    CHECK((f.versor()).x == doctest::Approx(0.7071));
    CHECK((f.versor()).y == doctest::Approx(0.7071));
    CHECK_THROWS(g.versor());
  }

  SUBCASE("Testing the toSfrml function") {
    gs::Vector a{1, 1};
    gs::Vector b{1, -1};
    gs::Vector c{0, -3};

    CHECK(a.toSfml() == sf::Vector2f{1, 1});
    CHECK(b.toSfml() == sf::Vector2f{1, -1});
    CHECK(c.toSfml() == sf::Vector2f{0, -3});
  }

  SUBCASE("Testing operator +=") {
    gs::Vector a{1, 1};
    gs::Vector b{2, 2};
    gs::Vector c{0, 0};
    gs::Vector d{-2, 0};
    gs::Vector e{-1, -1};

    CHECK((a += b) == gs::Vector{3, 3});  // qui a diventa {3,3}
    CHECK((a += a) ==
          gs::Vector{6, 6});  // qui  a è ancora {3,3} quindi quando faccio la
                              // somma con se stesso fa {6,6}
    CHECK((c += c) == gs::Vector{0, 0});
    CHECK((d += d) == gs::Vector{-4, 0});
    CHECK((d += b) == gs::Vector{-2, 2});   // qui d è {-4,0} e b {2,2}
    CHECK((e += a) == gs::Vector{5, 5});    // qui a è {6,6}
    CHECK((a += e) == gs::Vector{11, 11});  // qui a è {6,6} ma e{5,5}
  }

  SUBCASE("Testing operator ==") {
    gs::Vector a{1, 1};
    gs::Vector b{2, 2};
    gs::Vector c{0, 0};
    CHECK((a == a) == true);
    CHECK((a == b) == false);
    CHECK((c == c) == true);
  }

  SUBCASE("Testing operator +") {
    gs::Vector a{0, 0};
    gs::Vector b{0, 1};
    gs::Vector c{1, 0};
    gs::Vector e{0, -1};
    CHECK((a + a) == gs::Vector{0, 0});
    CHECK((b + b) == gs::Vector{0, 2});
    CHECK((c + b) == gs::Vector{1, 1});
    CHECK((e + b) == gs::Vector{0, 0});
    CHECK((c + e) == gs::Vector{1, -1});
  }

  SUBCASE("Testing operator -") {
    gs::Vector a{0, 0};
    gs::Vector d{1, 1};
    gs::Vector e{0, -1};
    CHECK((a - a) == gs::Vector{0, 0});
    CHECK((d - d) == gs::Vector{0, 0});
    CHECK((e - d) == gs::Vector{-1, -2});
    CHECK((a - d) == gs::Vector{-1, -1});
  }
  SUBCASE("Testing operator -") {
    gs::Vector a{0, 0};
    gs::Vector b{0, 1};
    gs::Vector c{1, 0};
    gs::Vector d{1, 1};
    gs::Vector e{0, -1};
    CHECK((-a) == gs::Vector{0, 0});
    CHECK((-b) == gs::Vector{0, -1});
    CHECK((-c) == gs::Vector{-1, 0});
    CHECK((-d) == gs::Vector{-1, -1});
    CHECK((-e) == gs::Vector{0, 1});
  }
  SUBCASE("Testing operator *") {
    gs::Vector a{0, 0};
    gs::Vector b{0, 1};
    gs::Vector c{1, -1};
    double e{0};
    double f{1};
    double g{-1};

    CHECK((e * a) == gs::Vector{0, 0});
    CHECK((e * b) == gs::Vector{0, 0});
    CHECK((a * f) == gs::Vector{0, 0});
    CHECK((b * f) == gs::Vector{0, 1});
    CHECK((c * g) == gs::Vector{-1, 1});
    CHECK((b * g) == gs::Vector{0, -1});
  }
  SUBCASE("Testing operator *") {
    gs::Vector a{0, 0};
    gs::Vector b{0, 1};
    gs::Vector c{1, -1};
    double e{0};
    double f{1};
    double g{-1};

    CHECK((a * e) == gs::Vector{0, 0});
    CHECK((b * e) == gs::Vector{0, 0});
    CHECK((f * a) == gs::Vector{0, 0});
    CHECK((f * b) == gs::Vector{0, 1});
    CHECK((g * c) == gs::Vector{-1, 1});
    CHECK((g * c) == gs::Vector{-1, 1});
  }
  SUBCASE("Testing operator /") {
    gs::Vector a{0, 0};
    gs::Vector b{0, 1};
    gs::Vector c{1, -1};
    double f{1};
    double g{-1};
    double h{0};
    CHECK_THROWS(a / h);
    CHECK((a / f) == gs::Vector{0, 0});
    CHECK((b / f) == gs::Vector{0, 1});
    CHECK((c / g) == gs::Vector{-1, 1});
    CHECK((c / f) == gs::Vector{1, -1});
  }
}

#endif