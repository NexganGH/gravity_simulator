#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <vector>

#include "../include/body.hpp"
#include "../include/configurations.hpp"
#include "../include/gui_manager.hpp"
#include "../include/orbit_drawer.hpp"
#include "../include/physics_engine.hpp"
#include "../include/renderer.hpp"
#include "../include/simulation_state.hpp"

int main() {
  OrbitDrawer orbitDrawer;

  auto height = sf::VideoMode::getDesktopMode().height - 100;

  sf::RenderWindow window(sf::VideoMode(height, height), "Gravity Simulator",
                          sf::Style::Titlebar);
  window.setPosition(sf::Vector2i(window.getPosition().x, 50));

  auto configurations = getConfigurations(window);
  auto conf = configurations[0];

  SimulationState state(conf);

  tgui::Gui gui{window};
  GuiManager guiManager(gui, state);  // added
  guiManager.createControlButtons();

  window.setFramerateLimit(60);

  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Time dt = deltaClock.restart();

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Right) {
          guiManager.rightButtonClicked(event);
        } else if (event.mouseButton.button == sf::Mouse::Left) {
          guiManager.leftButtonClicked(event);
        }
      }

      gui.handleEvent(event);
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
    guiManager.setYearsElapsed(ph->getSimulationSecondsElapsed() / 3.154E7,
                               ph->getTimeScale());
    orbitDrawer.draw(state.getRenderer(), timeElapsed);
    gui.draw();
    guiManager.drawArrow();

    window.display();
  }
}