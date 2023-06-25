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
  void applyGravity(std::unique_ptr<Body> &b1, std::unique_ptr<Body> &b2, double dt) {
    double X = b1->getPosition().x - b2->getPosition().x;
    double Y = b1->getPosition().y - b2->getPosition().y;
    double Xder = b1->getVelocity().x - b2->getVelocity().x;
    double Yder = b1->getVelocity().y - b2->getVelocity().y;
    //mod
    double Xderder=b1->getAcceleration().x-b2->getAcceleration().x;
    double Yderder=b1->getAcceleration().y-b2->getAcceleration().y;
    //mod
    Vector force;
    force.x = -G * (b1->getMass()) * (b2->getMass()) * X /
              std::pow(distance(b1, b2), 3);
    force.y = -G * (b1->getMass()) * (b2->getMass()) * Y /
              std::pow(distance(b1, b2), 3);
    b1->setForceUp(force);

//mod
//calcoliamo i parametri di RK oer le x 
double xk1=-G*b2->getMass()*X/std::pow(X*X+Y*Y,1.5);
double xk2=-G*b2->getMass()*(X+Xder*dt/2+Xderder*dt*dt/8)/std::pow(std::pow(X+Xder*dt/2+Xderder*dt*dt/8,2)+std::pow(Y+Yder*dt/2+Yderder*dt*dt/8,2),1.5);//*dt)/std::pow(std::pow(Xder+0.5*xk1*dt,2)+std::pow(Y+dt*Yder/2,2),1.5); //sarebe l'espasione di eulero di Y(t+dt/2);
double xk3=-G*b2->getMass()*(X+Xder*dt/2+Xderder*dt*dt/8)/std::pow(std::pow(X+Xder*dt/2+Xderder*dt*dt/8,2)+std::pow(Y+Yder*dt/2+Yderder*dt*dt/8,2),1.5);//check su questa 
double xk4=-G*b2->getMass()*(X+Xder*dt+0.5*Xderder*dt*dt)/std::pow(std::pow(X+Xder*dt+0.5*Xderder*dt*dt,2)+std::pow(Y+dt*Yder+0.5*Yderder*dt*dt,2),1.5);// check su questa 
b1->RKCxAddUp(0,xk1);
b1->RKCxAddUp(1,xk2);
b1->RKCxAddUp(2,xk3);
b1->RKCxAddUp(3,xk4);

//calcoliamo i parametri per RK per le y
double yk1=-G*b2->getMass()*Y/std::pow(Y*Y+X*X,1.5);
double yk2=-G*b2->getMass()*(Y+Yder*dt/2+Yderder*dt*dt/8)/std::pow(std::pow(X+Xder*dt/2+Xderder*dt*dt/8,2)+std::pow(Y+Yder*dt/2+Yderder*dt*dt/8,2),1.5);
double yk3=-G*b2->getMass()*(Y+Yder*dt/2+Yderder*dt*dt/8)/std::pow(std::pow(X+Xder*dt/2+Xderder*dt*dt/8,2)+std::pow(Y+Yder*dt/2+Yderder*dt*dt/8,2),1.5);
double yk4=-G*b2->getMass()*(Y+Yder*dt+Yderder*dt*dt)/std::pow(std::pow(X+Xder*dt+0.5*Xderder*dt*dt,2)+std::pow(Y+dt*Yder+Yderder*dt*dt,2),1.5);
b1->RKCyAddUp(0,yk1);
b1->RKCyAddUp(1,yk2);
b1->RKCyAddUp(2,yk3);
b1->RKCyAddUp(3,yk4);
//mod
  }
  
  void evolve(std::unique_ptr<Body> &b1, double dt) {
    auto pos = b1->getPosition();
    auto vel = b1->getVelocity();

    auto acc = b1->getAcceleration();

  //  auto newPosition = Vector{pos.x + vel.x * dt,
  //                             pos.y + vel.y * dt};
     auto newPosition = Vector{pos.x + vel.x * dt + 0.5 * acc.x * dt * dt,
                               pos.y + vel.y * dt + 0.5 * acc.y * dt * dt};
    b1->setPosition(newPosition);

    //mod
      vel.x = vel.x+dt*((b1->getRKCx())[0]+2*(b1->getRKCx())[1]+2*(b1->getRKCx())[2]+(b1->getRKCx())[3])/6;
      vel.y = vel.y+dt*((b1->getRKCy())[0]+2*(b1->getRKCy())[1]+2*(b1->getRKCy())[2]+(b1->getRKCy())[3])/6;
//mod
    b1->setVelocity(vel);
  }
};

#endif