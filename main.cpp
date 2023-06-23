#include "body.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "body.hpp"
#include "physics_engine.hpp"

int main() {
  std::vector<std::unique_ptr<Body>> bodies;
  PhysicsEngine ph;

  // "Vector" must be specified in order for make_unique to understand the type.
  std::unique_ptr<Body> p1 = std::make_unique<Planet>(Vector {800, 300}, Vector {-1, 3}, 1);
  std::unique_ptr<Body> p2 = std::make_unique<Planet>(Vector {700, 300}, Vector {-0.5, 0}, 10);


  bodies.push_back(std::move(p1));
  bodies.push_back(std::move(p2));

  sf::RenderWindow window(sf::VideoMode(1500, 1000), "Gravity Simulator");

  window.setFramerateLimit(60);

  while (window.isOpen()) {
    
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }


    // redrawing the scene
    window.clear();

    //MODIFICHE
//PRIMA faccio un ciclo dove calcolo per ciascun pianeta le forze totali riwultanti 
//TO DO 
for(auto it=bodies.begin(); it!=bodies.end(); ++it){
  for(auto is=bodies.begin(); is!=bodies.end(); ++is){
  PhysicsEngine ph;
  //se gli iteratori sono uguali puntano allo stesso pianeta per cui non posso calcolare la forza del pianeta che agisce su se stesso 
  //per cui gli faccio saltare se stesso
  if(it==is){
    is+=1;
  if(is>=bodies.end()){break;}
  }
   ph.applyGravity(*it,*is);
    
  
  }
}
//
//POI aplico evolve con le forze determinate per tutti 
for (auto it=bodies.begin(); it!=bodies.end(); ++it){
    PhysicsEngine ph;
    ph.evolve(*it, 0.2);
    window.draw(*((*it)->getShape())); // (*it) ottengo il puntatore (che sia shared o puntatore porprio) allo heap, (*it)->getShape mi ritorna il punattore sullo heap a circle (vedi tipo ritornato di  funzioen getshape), e dereferenzio questo per far disegnare porprio il cerchio che è allocato sullo heap punatto dal puntatore circle*

}

std::cout<<bodies[0]->getAcceleration().x<<"   "<< bodies[1]->getAcceleration().x<<"         "  <<bodies[0]->getPosition().x <<"   "<<bodies[1]->getPosition().x <<'\n';

//resetto le forze a zero per ricalcolarle con la funzione set force sum dopo;
for(auto it=bodies.begin(); it!=bodies.end(); ++it){
  (*it)->setForce({0,0});
  (*it)->setForce_deriv({0,0});
}

    


    window.display();
  }
}