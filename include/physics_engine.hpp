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

  double getTimeScale();

  void setTimeScale(double timeScale);

  bool isRunning();

  void toggleRunning();

  double getSimulationSecondsElapsed();
  double getRealSecondsElapsed();

  void resetTimeElapsed();
  void evolve(std::vector<std::unique_ptr<Body>> &bodies, double dt);

};

#endif