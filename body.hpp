#ifndef BODY_HPP
#define BODY_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Vector {
  double x;
  double y;
};

Vector operator+(Vector a, Vector b){return {a.x+b.x, a.y+b.y};}

class Body {
 protected:
  Vector _position;
  Vector _velocity;
  Vector _force;
   //mod//aggiunta
  std::array<double,4> _RKCx;
  std::array<double,4> _RKCy;
  //mod
  double _mass;

 public:
  Body(Vector position, Vector velocity, double mass)
      : _position{position}, _velocity{velocity}, _mass{mass} {
    // TODO: Add class invariants.
  }

  //MODIFICHE//
  double getMass() const { return _mass; }
  void setForceUp(Vector f){_force=_force+f;}
  //MODIFICHE//

//mod//aggiunte
  std::array<double,4> getRKCx() const{return _RKCx;}
  std::array<double,4> getRKCy() const{return _RKCy;}

//sommo i parametri k calcolati con i vari pianeti //verifica che sia corretto
  void RKCxAddUp(int a, double b){_RKCx[a]+=b;} //a deve essere compreso tra 0 e 3// come fare il chek?
  void RKCyAddUp(int a, double b){_RKCy[a]+=b;}

//alla fine di ogni evolve devo ricalcolare tutti i parametri k in funzione delle nuove posizioni quindi setto quelli che ci sono a zero
  void RKCxClear(){
    for(int i{0};i<3;++i){
      _RKCx[i]=0;
    }
  }

  void RKCyClear(){
    for(int i{0};i<3;++i){
      _RKCy[i]=0;
    }
  }
  
  //mod




  Vector getPosition() const { return _position; }

  void setPosition(Vector v) {
    // TODO: Add check that v.x, v.y >= 0.  //perchè?
    _position = v;
  }

  Vector getVelocity() const { return _velocity; }

  void setVelocity(Vector velocity) { _velocity = velocity; }

  Vector getForce() const { return _force; }

  void setForce(Vector force) { _force = force; }

  Vector getAcceleration() const {
    return { _force.x / _mass, _force.y / _mass };
  }

  virtual std::unique_ptr<sf::Shape> getShape() const = 0;
};

class Planet : public Body {
 public:
  Planet(Vector position, Vector velocity, double mass)
      : Body(position, velocity, mass) {}

  std::unique_ptr<sf::Shape> getShape() const override {
    std::unique_ptr<sf::Shape> circle = std::make_unique<sf::CircleShape>(5);
    circle->setFillColor(sf::Color::Blue);
    
    // Making body's size proportional to mass.
    auto size = sqrt(getMass()) * 10E-7 / 2.5;
    circle->setScale( size, size);
    std::cout<<size << "\n";

    circle->setPosition(_position.x, _position.y);
    return circle;
  }
};

#endif