#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "SFML/Graphics.hpp"
#include "body.hpp"
#include "physics_engine.hpp"
#include "renderer.hpp"

namespace gs {

/**
 * This is an initial setup of the simulation. Contains a name, the starting
 * bodies, the * universe width, the timescale.
 */
class Configuration {
 private:
  std::string _name;
  std::vector<std::unique_ptr<Body>> _bodies;
  double _universeWidth;
  double _timeScale;

  sf::RenderWindow& _window;

 public:
  Configuration(std::string name, double universeWidth, double timeScale,
                sf::RenderWindow& window);

  /**
   * Adds a body the the configuration.
   *
   * @param body The body being added to the configuration.
   */
  void addBody(std::unique_ptr<Body>& body);

  std::string getName() const;

  /**
   * Creates the Renderer, used to draw the objects on the screen.
   *
   * @return The pointer to the created renderer.
   */
  std::unique_ptr<Renderer> createRenderer() const;

  /**
   * Creates the PhysicsEngine object, used in the simulation to apply forces
   * and calculate body's position in each.
   *
   * @return The pointer to the created PhysicsEngine.
   */
  std::unique_ptr<PhysicsEngine> createPhysicsEngine() const;

  /**
   * Creates the bodies according to the configuration.
   *
   * @return A vector containing pointers to the bodies.
   */
  std::vector<std::unique_ptr<Body>> createBodies() const;

  // Configuration's fields make Configuration non-copyable.
  Configuration(const Configuration&) = delete;
  Configuration& operator=(Configuration&) = delete;
};

};  // namespace gs

#endif