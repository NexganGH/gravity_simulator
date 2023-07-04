#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "body.hpp"
#include "physics_engine.hpp"
#include "renderer.hpp"
#include "SFML/Graphics.hpp"

class Configuration {
 private:
  std::string _name;
  double _universeWidth;
  double _timeScale;
  std::vector<std::unique_ptr<Body>> _bodies;
  sf::RenderWindow& _window;

 public:
  Configuration(std::string name, double universeWidth, double timeScale, sf::RenderWindow& window)
      : _name(name), _universeWidth(universeWidth), _timeScale(timeScale), _window(window) {
    assert(universeWidth > 0);
    assert(_timeScale > 0);
  }

  void addBody(std::unique_ptr<Body>& body) {
    if (body == nullptr) throw std::invalid_argument("Body is nullptr.");

    _bodies.push_back(std::move(body));
  }

  std::unique_ptr<Renderer> createRenderer() {
    return Renderer::fromUniverseWidth(_window, _universeWidth);
  }

  std::unique_ptr<PhysicsEngine> createPhysicsEngine() {
    //PhysicsEngine ph(_timeScale);
    return std::make_unique<PhysicsEngine>(_timeScale);
  }

  std::vector<std::unique_ptr<Body>> createBodies() {
    std::vector<std::unique_ptr<Body>> bodies;
    for (auto& body : _bodies) {
      bodies.push_back(body->clone());
    }
    return bodies;
  }

  Configuration(const Configuration&) = delete;
  Configuration& operator=(Configuration&) = delete;
};

#endif