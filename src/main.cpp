#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "configurations.hpp"
#include "gui_manager.hpp"
#include "orbit_drawer.hpp"
#include "simulation_state.hpp"

int main() {
  gs::OrbitDrawer orbitDrawer;

  auto height = sf::VideoMode::getDesktopMode().height - 100;

  sf::RenderWindow window(sf::VideoMode(height, height), "Gravity Simulator",
                          sf::Style::Titlebar);
  window.setPosition(sf::Vector2i(window.getPosition().x, 50));

  auto configurations = gs::getConfigurations(window);
  auto conf = configurations[0];

  gs::SimulationState state(conf);

  gs::GuiManager guiManager(window, state);  // added
  guiManager.setup();

  window.setFramerateLimit(60);

  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Time dt = deltaClock.restart();

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear();

    auto& ph = state.getPhysicsEngine();
    auto& bodies = state.getBodies();
    ph->evolve(state.getBodies(), dt.asSeconds());

    double timeElapsed = ph->getRealSecondsElapsed();
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      orbitDrawer.addPoint((*it)->getPosition(), timeElapsed);
      state.getRenderer()->draw(*it);
    }

    // correct
    guiManager.updateValues(ph->getSimulationSecondsElapsed() / 3.154E7,
                            ph->getTimeScale());
    orbitDrawer.draw(state.getRenderer(), timeElapsed);
    guiManager.draw();

    window.display();
  }
}