#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <vector>

#include "body.hpp"
#include "configurations.hpp"
#include "gui_manager.hpp"
#include "orbit_drawer.hpp"
#include "physics_engine.hpp"
#include "renderer.hpp"

int main() {
  OrbitDrawer orbitDrawer;

  auto height = sf::VideoMode::getDesktopMode().height - 100;

  sf::RenderWindow window(sf::VideoMode(height, height), "Gravity Simulator",
                          sf::Style::Titlebar);
  window.setPosition(sf::Vector2i(window.getPosition().x, 50));

  auto configurations = getConfigurations();
  auto conf = configurations[0];

  auto bodies = std::move(conf->getBodies());

  auto ph = conf->getPhysicsEngine();
  auto render = conf->getRenderer(window);
  // added
  auto initial_states = conf->get_vector_of_itial_states();

  tgui::Gui gui{window};
  GuiManager guiManager{gui, ph, bodies, render, initial_states};  // added
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

    ph.evolve(bodies, dt.asSeconds());
    double TimeElapsed = ph.getRealSecondsElapsed();

    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      orbitDrawer.addPoint((*it)->getPosition(), TimeElapsed);
      render.draw(*it);
    }

    // correct
    guiManager.setYearsElapsed(ph.getSimulationSecondsElapsed() / 3.154E7,
                               ph.getTimeScale());
    orbitDrawer.draw(render, TimeElapsed);
    gui.draw();
    guiManager.drawArrow();

    window.display();
  }
}