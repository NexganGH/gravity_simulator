#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <SFML/Graphics.hpp>

#include "body.hpp"
#include "configurations.hpp"
#include "doctest.h"
#include "simulation_state.hpp"

TEST_CASE("Testing Renderer class") {
  sf::RenderWindow window;
  gs::Renderer renderer(window, 1);
  SUBCASE("Tetsing screenToReal class") {
    gs::Vector a{1, 1};
    gs::Vector b{0, 0};
    gs::Vector c{-1, -1};
    gs::Vector d = renderer.screenToReal(a);
    gs::Vector e = renderer.screenToReal(b);
    gs::Vector f = renderer.screenToReal(c);
    CHECK(a == d);
    CHECK(b == e);
    CHECK(c == f);
  }
  SUBCASE("Testing realToScreen") {
    sf::Vector2f a{1, 1};
    sf::Vector2f b{0, 0};
    sf::Vector2f c{-1, -1};
    sf::Vector2f d = renderer.realToScreen(a);
    sf::Vector2f e = renderer.realToScreen(b);
    sf::Vector2f f = renderer.realToScreen(c);
    CHECK(a == d);
    CHECK(b == e);
    CHECK(c == f);
  }
}