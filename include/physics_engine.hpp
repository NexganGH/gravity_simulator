#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE
#include <cassert>
#include <cmath>
#include <memory>

#include "body.hpp"

namespace gs {

/**
 * The class used to calculate the physics of the simulation. It:
 * - applies Gravity force.
 * - simulates body motion, evolving their position, velocity and force in time.
 */
class PhysicsEngine {
  // La vera costante è 6.67E-11
 private:
  const double G = 6.67E-11;
  double _timeScale = 1;
  bool _running = false;
  double _timeElapsed = 0;

  /**
   * First step of the leapfrog integration - see the report.
   * @param b1 The body to calculate the first step for.
   * @param dt The interval of time, already scaled correctly.
   */
  void firstStep(std::unique_ptr<Body> &b1, double dt) const;

  /**
   * Second step of the leapfrog integration - see the report.
   * @param b1 The body to calculate the second step for.
   * @param dt The interval of time, already scaled correctly.
   */
  void secondStep(std::unique_ptr<Body> &b1, double dt) const;

  /**
   * Applies gravity to BOTH the bodies according to each other's mass for
   * optimisation reasons.
   *
   * @param b1 The first body.
   * @param b2 The seocnd body (the gravity is applied to this body as well).
   */
  void applyGravity(std::unique_ptr<Body> &b1, std::unique_ptr<Body> &b2) const;

 public:
  PhysicsEngine(double timeScale);

  /**
   * @return The timescale, in seconds. It corresponds to how many seconds will
   * be simulated in a second in real life.
   */
  double getTimeScale() const;

  /**
   * Sets the timescale. It corresponds to how many seconds will be simulated in
   * a second in real life.
   */
  void setTimeScale(double timeScale);

  /**
   * @returns True if the simulation is running.
   */
  bool isRunning() const;

  /**
   * Stops the simulation if it is running or pause it if it is stopped.
   */
  void toggleRunning();

  /**
   * Gets how many simulation seconds have passed since the beginning of the
   * program.
   */
  double getSimulationSecondsElapsed() const;

  /**
   * Gets how many real seconds have passed since the beginning of the program.
   */
  double getRealSecondsElapsed() const;

  /**
   * Evolves the simulation of one step.
   *
   * @param dt is the amount of time, in seconds, to advance the simulation. It
   * should correspond to the amount of time in real life that occured from the
   * previous cycle. Use the `timeScale` parameter to speed up/slow down the
   * simulation.
   */
  void evolve(std::vector<std::unique_ptr<Body>> &bodies, double dt);
};

};  // namespace gs
#endif