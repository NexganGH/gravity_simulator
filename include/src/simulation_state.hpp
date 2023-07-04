#ifndef SIMULATION_STATE_H
#define SIMULATION_STATE_H

#include <vector>

#include "configuration.hpp"
#include "gui_manager.hpp"
#include "physics_engine.hpp"
#include "renderer.hpp"

class SimulationState {
 private:
  std::shared_ptr<Configuration> _configuration;
  std::vector<std::unique_ptr<Body>> _bodies;
  std::unique_ptr<PhysicsEngine> _physicsEngine;
  std::unique_ptr<Renderer> _renderer;

 public:
  SimulationState(std::shared_ptr<Configuration> conf)
      : _configuration(conf),
        _bodies(conf->createBodies()),
        _physicsEngine(conf->createPhysicsEngine()),
        _renderer(conf->createRenderer()) {}

  void reset() {
    _bodies = _configuration->createBodies();
    _physicsEngine = _configuration->createPhysicsEngine();
    _renderer = _configuration->createRenderer();
  }

  // void configure(std::shared_ptr<Configuration> conf) {
  //   _configuration = conf;
  // }

  std::vector<std::unique_ptr<Body>>& getBodies() { return _bodies; }
  std::unique_ptr<PhysicsEngine>& getPhysicsEngine() { return _physicsEngine; }
  std::unique_ptr<Renderer>& getRenderer() { return _renderer; }

  SimulationState(const SimulationState&) = delete;
  SimulationState& operator=(SimulationState&) = delete;
};

#endif