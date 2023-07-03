#ifndef DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
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
    // TEst con Vector{0,0}??
    Vector a{1, 1};
    Vector b{5, 0};
    Vector c{0, 3};
    Vector d{-2, 0};
    Vector e{0, -3};
    Vector f{3, 3};
    CHECK((a.versor()).x == doctest::Approx(0.7071));
    CHECK((a.versor()).y == doctest::Approx(0.7071));
    CHECK(b.versor() == Vector{1, 0});
    CHECK(c.versor() == Vector{0, 1});
    CHECK(d.versor() == Vector{-1, 0});
    CHECK(e.versor() == Vector{0, -1});
    CHECK((f.versor()).x == doctest::Approx(0.7071));
    CHECK((f.versor()).y == doctest::Approx(0.7071));
    }

  SUBCASE("Testing the toSfrml function") {
    Vector a{1, 1};
    Vector b{1, -1};
    Vector c{0, -3};

    CHECK(a.toSfml()==sf::Vector2f{1,1});
    CHECK(b.toSfml()==sf::Vector2f{1,-1});
    CHECK(c.toSfml()==sf::Vector2f{0,-3});
  }

  SUBCASE("Testing operator +="){
    Vector a{1, 1};
    Vector b{2, 2};
    Vector c{0, 0};
    Vector d{-2, 0};
    Vector e{-1,-1};
    CHECK((a+=b)==Vector{3,3});
    CHECK((a+=a)==Vector{2,2});//
    CHECK((c+=c)==Vector{0,0});
    CHECK((d+=d)==Vector{-4,0});//
    CHECK((d+=b)==Vector{0,2});//
    CHECK((e+=a)==Vector{0,0});//
    CHECK((a+=e)==Vector{0,0});//
  }

  SUBCASE("Testing operator =="){
    Vector a{1, 1};
    Vector b{2, 2};
    Vector c{0, 0};
    CHECK((a==a)==true);
    CHECK((a==b)==false);
    CHECK((c==c)==true);
  }

  SUBCASE("Testing operator +"){
    Vector a{0, 0};
    Vector b{0, 1};
    Vector c{1, 0};
    Vector e{0, -1};
    CHECK((a+a)==Vector{0,0});
    CHECK((b+b)==Vector{0,2});
    CHECK((c+b)==Vector{1,1});
    CHECK((e+b)==Vector{0,0});
    CHECK((c+e)==Vector{1,-1});

  }

  SUBCASE("Testing operator -"){
    Vector a{0, 0};
    Vector d{1, 1};
    Vector e{0, -1};
    CHECK((a-a)==Vector{0,0});
    CHECK((d-d)==Vector{0,0});
    CHECK((e-d)==Vector{-1,-2});
    CHECK((a-d)==Vector{-1,-1});

  }
  SUBCASE("Testing operator -"){
    Vector a{0, 0};
    Vector b{0, 1};
    Vector c{1, 0};
    Vector d{1, 1};
    Vector e{0, -1};
    CHECK((-a)==Vector{0,0});
    CHECK((-b)==Vector{0,-1});//fatto
    CHECK((-c)==Vector{-1,0});
    CHECK((-d)==Vector{-1,-1});
     CHECK((-e)==Vector{0,1});//fatto

  }
  SUBCASE("Testing operator *"){
    Vector a{0, 0};
    Vector b{0, 1};
    Vector c{1, -1};
    double e{0};
    double f{1};
    double g{-1};
   
    CHECK((e*a)==Vector{0,0});
    CHECK((e*b)==Vector{0,0});
    CHECK((a*f)==Vector{0,0});
    CHECK((b*f)==Vector{0,1});
    CHECK((c*g)==Vector{-1,1});
    CHECK((b*g)==Vector{0,-1});

  }
  SUBCASE("Testing operator *"){
    Vector a{0, 0};
    Vector b{0, 1};
    Vector c{1, -1};
    double e{0};
    double f{1};
    double g{-1};
    
    CHECK((a*e)==Vector{0,0});
    CHECK((b*e)==Vector{0,0});
    CHECK((f*a)==Vector{0,0});
    CHECK((f*b)==Vector{0,1});
    CHECK((g*c)==Vector{-1,1});
    CHECK((g*c)==Vector{-1,1});
  }
  SUBCASE("Testing operator /"){ //testa l'assert
    Vector a{0, 0};
    Vector b{0, 1};
    Vector c{1, -1};
    double f{1};
    double g{-1};
    CHECK((a/f)==Vector{0,0});
    CHECK((b/f)==Vector{0,1});//fatto
    CHECK((c/g)==Vector{-1,1});
    CHECK((c/f)==Vector{1,-1});

  }
  
}

#endif