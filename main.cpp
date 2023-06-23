#include "body.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

#include "body.hpp"
#include "physics_engine.hpp"

int main() {
  std::vector<std::unique_ptr<Body>> bodies;
  PhysicsEngine ph;

  auto p1 = std::make_unique<Body>(Vector {20, 20}, Vector {20, 20}, 5972E24);

  p1->setForce({100, 0});
  bodies.push_back(p1);

  sf::RenderWindow window(sf::VideoMode(1500, 1000), "Gravity Simulator");

  window.setFramerateLimit(60);

  while (window.isOpen()) {
    
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }


    // redrawing the scene
    window.clear();

    // for (auto it = bodies.begin(); it != bodies.end(); ++it) {
      
    // }

    // for (auto it = bodies.begin(); it != bodies.end() - 1; ++it) {
    //   //for (auto it2 = it; )
    // }

    for (std::unique_ptr<Body>& body : bodies ) {

      ph.evolve(body, 0.1);

      window.draw(*body->getShape());
    }

    window.display();
  }
}