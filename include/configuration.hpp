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
  Configuration(std::string name, double universeWidth, double timeScale, sf::RenderWindow& window);

  void addBody(std::unique_ptr<Body>& body);

  std::unique_ptr<Renderer> createRenderer();
  std::unique_ptr<PhysicsEngine> createPhysicsEngine();

  std::vector<std::unique_ptr<Body>> createBodies();

  Configuration(const Configuration&) = delete;
  Configuration& operator=(Configuration&) = delete;
};

#endif