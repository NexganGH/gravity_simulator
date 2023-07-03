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
  // added
  std::vector<Cuple_Vector> _vector_of_initial_states;

 public:
  Configuration(std::string name, double universeWidth, double timeScale)
      : _name(name), _universeWidth(universeWidth), _timeScale(timeScale) {
    assert(universeWidth > 0);
    assert(_timeScale > 0);
  }

  void addBody(std::unique_ptr<Body>& body) {
    if (body == nullptr)
      throw std::invalid_argument("Body is nullptr.");

    _bodies.push_back(std::move(body));
  }
  // added salvo gli stati iniziali in un vettore che deve essere lungo quanto
  // _bodies...verifica con un assert!!
  void save_initial_states() {
    for (auto it = _bodies.begin(); it != _bodies.end(); ++it) {
      Cuple_Vector a{(*it)->getPosition(), (*it)->getVelocity()};
      _vector_of_initial_states.push_back(a);
    }
  }
  // added
  std::vector<Cuple_Vector> get_vector_of_itial_states() const {
    return _vector_of_initial_states;
  }

  Renderer getRenderer(sf::RenderWindow& window) {
    auto renderer = Renderer::fromUniverseWidth(window, _universeWidth);

    return renderer;
  }

  PhysicsEngine getPhysicsEngine() {
    PhysicsEngine ph(_timeScale);
    return ph;
  }

  std::vector<std::unique_ptr<Body>>& getBodies() { return _bodies; }

  Configuration(const Configuration&) = delete;
  Configuration& operator=(Configuration&) = delete;
};

#endif