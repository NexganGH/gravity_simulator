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
  // std::vector<std::unique_ptr<Body>> bodies;
  // PhysicsEngine ph(500000);
  OrbitDrawer orbitDrawer;

  sf::RenderWindow window(sf::VideoMode(1500, 1500), "Gravity Simulator");
  //auto render = earthAndSun(bodies, window);

  auto configurations = getConfigurations();
  auto conf = configurations.at(0);

  std::vector<std::unique_ptr<Body>>& bodies = conf->getBodies();
  auto ph = conf->getPhysicsEngine();
  auto render = conf->getRenderer(window);

  tgui::Gui gui{window};
  GuiManager guiManager{gui, ph, bodies, render};
  guiManager.controlButtons();

  window.setFramerateLimit(60);

  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Time dt = deltaClock.restart();

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();

      if (event.type == sf::Event::MouseButtonPressed)
        if (event.mouseButton.button == sf::Mouse::Right)
          guiManager.rightButtonClicked(event);
      gui.handleEvent(event);
    }

    // redrawing the scene
    window.clear();

    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      for (auto is = bodies.begin(); is != bodies.end(); ++is) {
        // se gli iteratori sono uguali puntano allo stesso pianeta per cui non
        // posso calcolare la forza del pianeta che agisce su se stesso per cui
        // gli faccio saltare se stesso
        if (it != is) ph.applyGravity(*it, *is);
      }
    }

    // POI aplico evolve con le forze determinate per tutti
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      ph.evolve(*it, dt.asSeconds());
      orbitDrawer.addPoint((*it)->getPosition());
      render.draw(*it);
      //     (*it)->getShape()));  // (*it) ottengo il puntatore (che sia shared
      //     o
      // puntatore porprio) allo heap, (*it)->getShape
      // mi ritorna il punattore sullo heap a circle
      // (vedi tipo ritornato di  funzioen getshape),
      // e dereferenzio questo per far disegnare
      // porprio il cerchio che è allocato sullo heap
      // punatto dal puntatore circle*
    }

    // resetto le forze a zero per ricalcolarle con la funzione set force sum
    // dopo;
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      (*it)->resetForces();
    }

    guiManager.setTimeElapsed(ph.getTimeElapsed() / 3.154E7);
    orbitDrawer.draw(render);
    gui.draw();

    window.display();
  }
}