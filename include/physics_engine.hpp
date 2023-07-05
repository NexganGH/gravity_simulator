#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE
#include <cassert>
#include <cmath>
#include <memory>

#include "body.hpp"

class PhysicsEngine {
  // La vera costante è 6.67E-11
 private:
  const double G = 6.67E-11;
  double _timeScale = 1;
  bool _running = false;
  double _timeElapsed = 0;

  void firstStep(std::unique_ptr<Body> &b1, double dt);

  void secondStep(std::unique_ptr<Body> &b1, double dt);

  void applyGravity(std::unique_ptr<Body> &b1, std::unique_ptr<Body> &b2);

 public:
  PhysicsEngine(double timeScale);

  /**
   * @return The timescale, in seconds. It corresponds to how many seconds will be simulated in a second in real life.
  */
  double getTimeScale();

  /**
   * Sets the timescale. It corresponds to how many seconds will be simulated in a second in real life.
  */
  void setTimeScale(double timeScale);

  /**
   * @returns True if the simulation is running.
  */
  bool isRunning();

  /**
   * Stops the simulation if it is running or pause it if it is stopped.
  */
  void toggleRunning();

  /**
   * Gets how many simulation seconds have passed since the beginning of the program.
  */
  double getSimulationSecondsElapsed();

  /**
   * Gets how many real seconds have passed since the beginning of the program.
  */
  double getRealSecondsElapsed();

  /**
   * Evolves the simulation of one step.
   * 
   * @param dt is the amount of time, in seconds, to advance the simulation. It should correspond to the amount of time in real life that occured from the 
   * previous cycle. Use the `timeScale` parameter to speed up/slow down the simulation.
  */
  void evolve(std::vector<std::unique_ptr<Body>> &bodies, double dt);

};

#endif