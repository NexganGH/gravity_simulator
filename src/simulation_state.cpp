#include <vector>

#include "configuration.hpp"
#include "gui_manager.hpp"
#include "physics_engine.hpp"
#include "renderer.hpp"

namespace gs {

SimulationState::SimulationState(std::shared_ptr<Configuration> conf)
    : _configuration(conf),
      _bodies(conf->createBodies()),
      _physicsEngine(conf->createPhysicsEngine()),
      _renderer(conf->createRenderer()) {}

void SimulationState::reset(std::shared_ptr<Configuration> conf) {
  if (conf) {
    _configuration = conf;
  }

  _bodies = _configuration->createBodies();
  _physicsEngine = _configuration->createPhysicsEngine();
  _renderer = _configuration->createRenderer();
}

std::vector<std::unique_ptr<Body>>& SimulationState::getBodies() {
  return _bodies;
}
std::unique_ptr<PhysicsEngine>& SimulationState::getPhysicsEngine() {
  return _physicsEngine;
}
std::unique_ptr<Renderer>& SimulationState::getRenderer() { return _renderer; }

};  // namespace gs
