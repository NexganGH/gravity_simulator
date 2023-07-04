

#include <vector>

#include "../include/configuration.hpp"
#include "../include/gui_manager.hpp"
#include "../include/physics_engine.hpp"
#include "../include/renderer.hpp"


  SimulationState::SimulationState(std::shared_ptr<Configuration> conf)
      : _configuration(conf),
        _bodies(conf->createBodies()),
        _physicsEngine(conf->createPhysicsEngine()),
        _renderer(conf->createRenderer()) {}

  void SimulationState::reset() {
    _bodies = _configuration->createBodies();
    _physicsEngine = _configuration->createPhysicsEngine();
    _renderer = _configuration->createRenderer();
  }

  std::vector<std::unique_ptr<Body>>& SimulationState::getBodies() { return _bodies; }
  std::unique_ptr<PhysicsEngine>& SimulationState::getPhysicsEngine() { return _physicsEngine; }
  std::unique_ptr<Renderer>& SimulationState::getRenderer() { return _renderer; }

  // SimulationState::SimulationState(const SimulationState&) = delete;
  // SimulationState& SimulationState::operator=(SimulationState&) = delete;


