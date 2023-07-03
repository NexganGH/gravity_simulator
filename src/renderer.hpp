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
  sf::RenderWindow& _window;  // perchè per reference? perchè per il costruttore
                              // si prene per reference?

  // Example: if scale = 2 => Real distance between two objects is
  // (screenDistance)*2 (in meters) If scale = 1, the 1 pixel = 1 meter.
  double _scale;

  double realToScreen(double real) { return real / _scale; }
  double screenToReal(double screen) { return screen * _scale; }

 public:
  Renderer(sf::RenderWindow& window, double scale)
      : _window(window), _scale(scale) {
    assert(_scale > 0);
  }

  static std::unique_ptr<Renderer> fromUniverseWidth(sf::RenderWindow& window,
                                    double universeWidth) {
    return std::make_unique<Renderer>(window, universeWidth / window.getView().getSize().x);
  }

  double getUniverseHeight() { return _window.getView().getSize().y * _scale; }

  void draw(std::unique_ptr<Body>& body) { draw(*(body->getShape(_scale))); }

  void draw(sf::Shape& shape) {
    auto pos = realToScreen(shape.getPosition());

    auto rect = shape.getLocalBounds();
    shape.setPosition(pos.x - rect.width / 2, pos.y - rect.height / 2);
    _window.draw(shape);
  }

  void drawGui(sf::VertexArray& shape) { _window.draw(shape); }

  Vector screenToReal(Vector screen) {
    Vector real{screenToReal(screen.x), screenToReal(screen.y)};
    return real;
  }

  sf::Vector2f realToScreen(sf::Vector2f real) {
    return sf::Vector2f(realToScreen(real.x), realToScreen(real.y));
  }
  // coverte un vettore di sfml da reale a screen usando il metodo che si trova
  // nella parte privata

  sf::Vector2f getMousePosition() {
    return sf::Vector2f(sf::Mouse::getPosition(_window));
  }

  Renderer(const Renderer& renderer)
      : _window(renderer._window), _scale(renderer._scale) {}
  // non c'è bisogno di definire l'operatore = per fare il copy constructor
  // perchè lo genera automaticamnte una volta noto il copy constructor qui
  // definito
};

#endif
