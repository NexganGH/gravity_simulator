#ifndef DISTANCE_CALCULATOR_H
#define DISTANCE_CALCULATOR_H

#include <bits/stdc++.h>

#include <SFML/Graphics.hpp>

#include "body.hpp"

/**
 * Class used to properly calculate the distance between two objects, in order
 * to render them properly on the screen.
 */
class Renderer {
 private:
  sf::RenderWindow& _window;

  // Example: if scale = 2 => Real distance between two objects is
  // (screenDistance)*2 (in meters) If scale = 1, the 1 pixel = 1 meter.
  double _scale;

  double realToScreen(double real) { return real / _scale; }

  sf::Vector2f realToScreen(sf::Vector2f real) {
    return sf::Vector2f(realToScreen(real.x), realToScreen(real.y));
  }

 public:
  Renderer(sf::RenderWindow& window, double scale)
      : _window(window), _scale(scale) {
    assert(_scale > 0);
  }

  static Renderer fromUniverseWidth(sf::RenderWindow& window,
                                    double universeWidth) {
    return Renderer(window, universeWidth / window.getView().getSize().x);
  }

  double getUniverseHeight() { return _window.getView().getSize().y * _scale; }

  void draw(std::unique_ptr<Body>& body) { draw(*(body->getShape())); }

  void draw(sf::Shape& shape) {
    auto pos = realToScreen(shape.getPosition());

    auto rect = shape.getLocalBounds();
    shape.setPosition(
        sf::Vector2f(pos.x - rect.width / 2, pos.y - rect.height / 2));
    _window.draw(shape);
  }

  Vector screenToReal(Vector screen) { return _scale * screen; }

  Renderer(const Renderer& renderer)
      : _window(renderer._window), _scale(renderer._scale) {}
};

#endif