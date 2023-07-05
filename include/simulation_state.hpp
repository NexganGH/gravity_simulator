#ifndef SIMULATION_STATE_H
#define SIMULATION_STATE_H

#include <vector>

#include "configuration.hpp"
#include "physics_engine.hpp"
#include "renderer.hpp"

namespace gs {

class SimulationState {
 private:
  std::shared_ptr<Configuration> _configuration;
  std::vector<std::unique_ptr<Body>> _bodies;
  std::unique_ptr<PhysicsEngine> _physicsEngine;
  std::unique_ptr<Renderer> _renderer;

 public:
  SimulationState(std::shared_ptr<Configuration> conf);

  void reset();

  std::vector<std::unique_ptr<Body>>& getBodies();
  std::unique_ptr<PhysicsEngine>& getPhysicsEngine();
  std::unique_ptr<Renderer>& getRenderer();

  SimulationState(const SimulationState&) = delete;
  SimulationState& operator=(SimulationState&) = delete;
};

};  // namespace gs

#endif