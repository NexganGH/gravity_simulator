
#include "renderer.hpp"

#include <bits/stdc++.h>

#include <SFML/Graphics.hpp>

#include "body.hpp"

namespace gs {

double Renderer::realToScreen(double real) { return real / _scale; }
double Renderer::screenToReal(double screen) { return screen * _scale; }

Renderer::Renderer(sf::RenderWindow& window, double scale)
    : _window(window), _scale(scale) {
  assert(_scale > 0);
}

std::unique_ptr<Renderer> Renderer::fromUniverseWidth(sf::RenderWindow& window,
                                                      double universeWidth) {
  return std::make_unique<Renderer>(
      window, universeWidth / window.getView().getSize().x);
}

double Renderer::getUniverseWidth() {
  return _window.getView().getSize().x * _scale;
}

double Renderer::getUniverseHeight() {
  return _window.getView().getSize().y * _scale;
}

void Renderer::draw(std::unique_ptr<Body>& body) {
  draw(*(body->getShape(_scale)));
}

void Renderer::draw(sf::Shape& shape) {
  auto pos = realToScreen(shape.getPosition());

  auto rect = shape.getLocalBounds();
  shape.setPosition(pos.x - rect.width / 2, pos.y - rect.height / 2);
  _window.draw(shape);
}

void Renderer::drawGui(sf::VertexArray& shape) { _window.draw(shape); }

Vector Renderer::screenToReal(Vector screen) {
  Vector real{screenToReal(screen.x), screenToReal(screen.y)};
  return real;
}

sf::Vector2f Renderer::realToScreen(sf::Vector2f real) {
  return sf::Vector2f(realToScreen(real.x), realToScreen(real.y));
}
// coverte un vettore di sfml da reale a screen usando il metodo che si trova
// nella parte privata

sf::Vector2f Renderer::getMousePosition() {
  return sf::Vector2f(sf::Mouse::getPosition(_window));
}

Renderer::Renderer(const Renderer& renderer)
    : _window(renderer._window), _scale(renderer._scale) {}

};  // namespace gs