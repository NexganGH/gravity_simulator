

#include "configuration.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "body.hpp"
#include "physics_engine.hpp"
#include "renderer.hpp"

namespace gs {

Configuration::Configuration(std::string name, double universeWidth,
                             double timeScale, sf::RenderWindow& window)
    : _name(name),
      _universeWidth(universeWidth),
      _timeScale(timeScale),
      _window(window) {
  assert(universeWidth > 0);
  assert(_timeScale > 0);
}

void Configuration::addBody(std::unique_ptr<Body>& body) {
  if (body == nullptr) throw std::invalid_argument("Body is nullptr.");

  _bodies.push_back(std::move(body));
}

std::string Configuration::getName() const { return _name; }

std::unique_ptr<Renderer> Configuration::createRenderer() const {
  return Renderer::fromUniverseWidth(_window, _universeWidth);
}

std::unique_ptr<PhysicsEngine> Configuration::createPhysicsEngine() const {
  // PhysicsEngine ph(_timeScale);
  return std::make_unique<PhysicsEngine>(_timeScale);
}

std::vector<std::unique_ptr<Body>> Configuration::createBodies() const {
  std::vector<std::unique_ptr<Body>> bodies;
  for (auto& body : _bodies) {
    bodies.push_back(body->clone());
  }
  return bodies;
}

};  // namespace gs