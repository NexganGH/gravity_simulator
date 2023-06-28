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

  sf::RenderWindow window(sf::VideoMode(1500, 1500), "Gravity Simulator");

  auto configurations = getConfigurations();
  auto conf = configurations[0];

  std::vector<std::unique_ptr<Body>>& bodies = conf->getBodies();
  auto ph = conf->getPhysicsEngine();
  auto render = conf->getRenderer(window);

  tgui::Gui gui{window};
  GuiManager guiManager{gui, ph, bodies, render};
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
        }
      }

      gui.handleEvent(event);
    }

    window.clear();

    for (auto it = bodies.begin(); it != bodies.end() - 1; ++it) {
      for (auto is = it + 1; is != bodies.end(); ++is) {
        if (it != is) ph.applyGravity(*it, *is);
      }
    }

    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      ph.evolve(*it, dt.asSeconds());
      orbitDrawer.addPoint((*it)->getPosition());
      render.draw(*it);
    }

    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      (*it)->resetForces();
    }

    for (auto it = bodies.begin(); it != bodies.end() - 1; ++it) {
      for (auto is = it + 1; is != bodies.end(); ++is) {
        if (it != is) ph.applyGravity(*it, *is);
      }
    }

    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      ph.ev(*it, dt.asSeconds());
    }
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      (*it)->resetForces();
    }

    guiManager.setYearsElapsed(ph.getSecondsElapsed() / 3.154E7);
    orbitDrawer.draw(render);
    gui.draw();

    window.display();
  }
}