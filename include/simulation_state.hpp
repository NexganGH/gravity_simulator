#ifndef SIMULATION_STATE_H
#define SIMULATION_STATE_H

#include <vector>

#include "configuration.hpp"
#include "physics_engine.hpp"
#include "renderer.hpp"

namespace gs {

/**
 * A class to represents the current state of the simulation.
 */
class SimulationState {
 private:
  // This is the configuration being used.
  std::shared_ptr<Configuration> _configuration;

  // These are the bodies in simulation.
  std::vector<std::unique_ptr<Body>> _bodies;

  // This is the physics engine used to simulate. Calculates gravity, body
  // evolution.
  std::unique_ptr<PhysicsEngine> _physicsEngine;

  // This is the renderer.
  std::unique_ptr<Renderer> _renderer;

 public:
  SimulationState(std::shared_ptr<Configuration> conf);

  /**
   * Resets the simulation state to initial values, according to the
   * configuration.
   *
   * @param conf If passed, resets according to this configuration. If not
   * passed, resets * according to the configuration in use.
   */
  void reset(std::shared_ptr<Configuration> conf = nullptr);

  /**
   * @return Pointers to the bodies in the simulation.
   */
  std::vector<std::unique_ptr<Body>>& getBodies();

  /**
   * @return Pointer to PhysicsEngine used in the simulation.
   */
  std::unique_ptr<PhysicsEngine>& getPhysicsEngine();

  /**
   * @return Pointer to the renderer used in the simulation.
   */
  std::unique_ptr<Renderer>& getRenderer();

  // Cannot be copied.
  SimulationState(const SimulationState&) = delete;
  SimulationState& operator=(SimulationState&) = delete;
};

};  // namespace gs

#endif