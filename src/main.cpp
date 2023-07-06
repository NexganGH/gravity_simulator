#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "configurations.hpp"
#include "gui_manager.hpp"
#include "orbit_drawer.hpp"
#include "simulation_state.hpp"

int main() {
  sf::Clock deltaClock;

  // Adapting the height to user's window height.
  auto height = sf::VideoMode::getDesktopMode().height - 100;

  sf::RenderWindow window(sf::VideoMode(height, height), "Gravity Simulator",
                          sf::Style::Titlebar);
  window.setPosition(sf::Vector2i(window.getPosition().x, 50));

  std::srand(std::time(NULL));
  auto configurations = gs::getConfigurations(window);
  auto conf = configurations[0];

  gs::SimulationState state(conf);

  gs::GuiManager guiManager(window, state, configurations);  // added
  guiManager.setup();

  window.setFramerateLimit(60);

  while (window.isOpen()) {
    sf::Time dt = deltaClock.restart();

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      guiManager.handleEvent(event);
    }

    window.clear();

    auto& ph = state.getPhysicsEngine();
    auto& bodies = state.getBodies();

    // Step of the simulation - dt is the real time passed since the previous
    // step.
    ph->evolve(state.getBodies(), dt.asSeconds());

    // Drawing all the bodies
    double timeElapsed = ph->getRealSecondsElapsed();
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      // Adds the point of the orbit on the drawer.
      guiManager.addOrbitPoint((*it)->getPosition(), timeElapsed);
      state.getRenderer()->draw(*it);
    }

    guiManager.updateValues(ph->getSimulationSecondsElapsed() / 3.154E7,
                            ph->getTimeScale());
    guiManager.draw();

    window.display();
  }
}