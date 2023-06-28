#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "body.hpp"
#include "physics_engine.hpp"
#include "renderer.hpp"

class Configuration {
 private:
  std::string _name;
  double _universeWidth;
  double _timeScale;
  std::vector<std::unique_ptr<Body>> _bodies;

 public:
  Configuration(std::string name, double universeWidth, double timeScale)
      : _name(name), _universeWidth(universeWidth), _timeScale(timeScale) {
  }

  void addBody(std::unique_ptr<Body>& body) {
    _bodies.push_back(std::move(body));
  }

  Renderer getRenderer(sf::RenderWindow& window) {
    auto renderer = Renderer::fromUniverseWidth(window, _universeWidth);

    return renderer;
  }

  PhysicsEngine getPhysicsEngine() {
    PhysicsEngine ph(_timeScale);
    return ph;
  }

  std::vector<std::unique_ptr<Body>>& getBodies() {
    return _bodies;
  }

  Configuration(const Configuration&) = delete;
  Configuration& operator=(Configuration&) = delete;
};

#endif