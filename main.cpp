#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "body.hpp"
#include "physics_engine.hpp"
#include "configurations.hpp"

int main() {
  std::vector<std::unique_ptr<Body>> bodies;
  PhysicsEngine ph;

  // // "Vector" must be specified in order for make_unique to understand the
  // type. std::unique_ptr<Body> p1 =
  //     std::make_unique<Planet>(Vector{800, 800}, Vector{-10, 10}, 10E12);
  // std::unique_ptr<Body> p2 =
  //     std::make_unique<Planet>(Vector{700, 300}, Vector{-0.5, 0}, 10E13);

  // bodies.push_back(std::move(p1));
  // bodies.push_back(std::move(p2));


  //binaryStars(bodies);
  //threeBodies(bodies);
  //collapsingBinaryStars(bodies);
  stableOrbitTwoPlanets(bodies);

  sf::RenderWindow window(sf::VideoMode(1500, 1000), "Gravity Simulator");

  window.setFramerateLimit(120);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    // redrawing the scene
    window.clear();

    // MODIFICHE
    // PRIMA faccio un ciclo dove calcolo per ciascun pianeta le forze totali
    // riwultanti
    // TODO:
    //  Volendo si può modificare la funzione applyGravity in modo che applichi
    //  la gravità a entrambi. Così facendo si può modificare questo algoritmo
    //  facendo partire il secondo ciclo dall'iteratore it (is = it). Così il
    //  numero di operazioni si riduce significativamente, da n^2 -> n + (n-1) +
    //  (n-2) + ... + 1
    // Con anche solo 10 corpi si riduce il numero di cicli da 100 a 55 !
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      for (auto is = bodies.begin(); is != bodies.end(); ++is) {
        PhysicsEngine ph;
        // se gli iteratori sono uguali puntano allo stesso pianeta per cui non
        // posso calcolare la forza del pianeta che agisce su se stesso per cui
        // gli faccio saltare se stesso
        if (it == is) {
          is += 1;
          if (is >= bodies.end()) {
            break;
          }
        }
        ph.applyGravity(*it, *is);
      }
    }

    // POI aplico evolve con le forze determinate per tutti
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      PhysicsEngine ph;
      ph.evolve(*it, 0.2);
      window.draw(*(
          (*it)->getShape()));  // (*it) ottengo il puntatore (che sia shared o
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
      (*it)->setForce({0, 0});
      (*it)->setForce_deriv({0, 0});
      //mod
      (*it)->setForce2deriv({0,0});
      
    }

    window.display();
  }
}