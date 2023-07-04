

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "../include/body.hpp"
#include "../include/physics_engine.hpp"
#include "../include/renderer.hpp"
#include "../include/configuration.hpp"
#include "SFML/Graphics.hpp"


 
  Configuration::Configuration(std::string name, double universeWidth, double timeScale, sf::RenderWindow& window)
      : _name(name), _universeWidth(universeWidth), _timeScale(timeScale), _window(window) {
    assert(universeWidth > 0);
    assert(_timeScale > 0);
  }

  void Configuration::addBody(std::unique_ptr<Body>& body) {
    if (body == nullptr) throw std::invalid_argument("Body is nullptr.");

    _bodies.push_back(std::move(body));
  }

  std::unique_ptr<Renderer> Configuration::createRenderer() {
    return Renderer::fromUniverseWidth(_window, _universeWidth);
  }

  std::unique_ptr<PhysicsEngine> Configuration::createPhysicsEngine() {
    //PhysicsEngine ph(_timeScale);
    return std::make_unique<PhysicsEngine>(_timeScale);
  }

  std::vector<std::unique_ptr<Body>> Configuration::createBodies() {
    std::vector<std::unique_ptr<Body>> bodies;
    for (auto& body : _bodies) {
      bodies.push_back(body->clone());
    }
    return bodies;
  }

  // Configuration::Configuration(const Configuration&) = delete;
  // Configuration& Configuration::operator=(Configuration&) = delete;


