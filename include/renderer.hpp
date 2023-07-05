#ifndef DISTANCE_CALCULATOR_H
#define DISTANCE_CALCULATOR_H

#include <bits/stdc++.h>

#include <SFML/Graphics.hpp>

#include "body.hpp"

namespace gs {

/**
 * Class used to properly calculate the distance between two objects, in order
 * to render them properly on the screen.
 */
class Renderer {
 private:
  sf::RenderWindow& _window;  // perchè per reference? perchè per il costruttore
                              // si prene per reference?

  // Example: if scale = 2 => Real distance between two objects is
  // (screenDistance)*2 (in meters) If scale = 1, the 1 pixel = 1 meter.
  double _scale;

  double realToScreen(double real);
  double screenToReal(double screen);

 public:
  Renderer(sf::RenderWindow& window, double scale);

  // qui ho dovuto togliere lo static
  static std::unique_ptr<Renderer> fromUniverseWidth(sf::RenderWindow& window,
                                                     double universeWidth);

  double getUniverseHeight();

  void draw(std::unique_ptr<Body>& body);

  void draw(sf::Shape& shape);

  void drawGui(sf::VertexArray& shape);

  Vector screenToReal(Vector screen);

  sf::Vector2f realToScreen(sf::Vector2f real);
  // coverte un vettore di sfml da reale a screen usando il metodo che si trova
  // nella parte privata

  sf::Vector2f getMousePosition();

  Renderer(const Renderer& renderer);
};

};  // namespace gs

#endif
