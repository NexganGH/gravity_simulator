#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE
#include <cmath>
#include <memory>

#include "body.hpp"

class PhysicsEngine {
  // La vera costante è 6.67E-11
  const float G = 6.67E-11;

 public:
  // MODIFICHE//
  /* TODO:
    * Inserire un fattore di scala, in questo modo le distanze tra i pianeti sono più grandi (come nella realtà) e si possono usare le masse reali.
    * Rendere distance() una funzione membro di planet (oppure usare direttamente l'operatore '-', vedi dopo)
    * Implementare le operazioni tra vettori: v1-v2 per la distanza, k*v1 per riscalare, ecc...
    * Derivata prima della forza
    * 
  */
  double distance(std::unique_ptr<Body> &b1, std::unique_ptr<Body> &b2) {
    return std::sqrt(std::pow(b1->getPosition().x - b2->getPosition().x, 2) +
                     std::pow(b1->getPosition().y - b2->getPosition().y, 2));
  }

  // il primo argomento ella funzione deve essere il pianeta di nostro interesse
  void applyGravity(std::unique_ptr<Body> &b1, std::unique_ptr<Body> &b2) {
    double X = b1->getPosition().x - b2->getPosition().x;
    double Y = b1->getPosition().y - b2->getPosition().y;
    double Xder = b1->getVelocity().x - b2->getVelocity().x;
    double Yder = b1->getVelocity().y - b2->getVelocity().y;
    Vector force;
    Vector force_der;

    // if(X<0){
    force.x = -G * (b1->getMass()) * (b2->getMass()) * X /
              std::pow(distance(b1, b2), 3);
    // force_der.x = -G * (b1->getMass()) * (b2->getMass()) *
    //               ((Xder * std::pow(distance(b1, b2), 6)) -
    //                1.5 * X * (2 * X * Xder + 2 * Y * Yder)) /
    //               std::pow(distance(b1, b2), 5);
    // } else {
    // force.x=G*(b1->getMass())*(b2->getMass())*X/std::pow(distance(b1,b2),3);
    // force_der.x=G*(b1->getMass())*(b2->getMass())*((Xder*std::pow(distance(b1,b2),6))-1.5*X*(2*X*Xder+2*Y*Yder))/std::pow(distance(b1,b2),5);
    // }

    // Qui la distanza era elevata alla 3a anziché alla 2a. Credo fosse sbagliato
    force.y = -G * (b1->getMass()) * (b2->getMass()) * Y /
              std::pow(distance(b1, b2), 3);
    // force_der.y = -G * (b1->getMass()) * (b2->getMass()) *
    //               ((Yder * std::pow(distance(b1, b2), 6)) -
    //                1.5 * Y * (2 * X * Xder + 2 * Y * Yder)) /
    //               std::pow(distance(b1, b2), 5);
    // } else {
    // force.y=G*(b1->getMass())*(b2->getMass())*Y/std::pow(distance(b1,b2),3);
    // force_der.y=G*(b1->getMass())*(b2->getMass())*((Yder*std::pow(distance(b1,b2),6))-1.5*Y*(2*X*Xder+2*Y*Yder))/std::pow(distance(b1,b2),5);
    // }

    // Qui c'era setForceUp.. perché?
    b1->setForceUp(force);

    // Da implementare in EVOLVE 
    b1->setForce_derivUp(force_der);
  }
  // MODIFICHE//
  void evolve(std::unique_ptr<Body> &b1, double dt) {
    auto pos = b1->getPosition();
    auto vel = b1->getVelocity();

    auto acc = b1->getAcceleration();

    // implementazione eulero

    // auto newPosition = Vector { pos.x + vel.x * dt +
    // 0.5*acc.x*dt*dt+0.1666667*b1->getAccDer().x*dt*dt*dt, pos.y + vel.y * dt
    // + 0.5*acc.y *dt* dt+0.1666667*b1->getAccDer().y*dt*dt*dt};
    auto newPosition = Vector{pos.x + vel.x * dt + 0.5 * acc.x * dt * dt,
                              pos.y + vel.y * dt + 0.5 * acc.y * dt * dt};
    b1->setPosition(newPosition);

    vel.x = vel.x + acc.x * dt;  //+0.5*b1->getAccDer().x*dt*dt;
    vel.y = vel.y + acc.y * dt;  //+0.5*b1->getAccDer().y*dt*dt;
    b1->setVelocity(vel);
  }
};

#endif