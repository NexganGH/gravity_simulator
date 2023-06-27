#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE
#include <cassert>
#include <cmath>
#include <memory>

#include "body.hpp"

class PhysicsEngine {
  // La vera costante è 6.67E-11
 private:
  const double G = 6.67E-11;
  double _timeScale = 1;

 public:
  PhysicsEngine(double timeScale) : _timeScale(timeScale) {
    assert(_timeScale > 0);
  }

  // MODIFICHE//
  /* TODO:
   * Inserire un fattore di scala, in questo modo le distanze tra i pianeti sono
   * più grandi (come nella realtà) e si possono usare le masse reali. Rendere
   * distance() una funzione membro di planet (oppure usare direttamente
   * l'operatore '-', vedi dopo) Implementare le operazioni tra vettori: v1-v2
   * per la distanza, k*v1 per riscalare, ecc... Derivata prima della forza
   *
   */

  // il primo argomento ella funzione deve essere il pianeta di nostro interesse
  void applyGravity(std::unique_ptr<Body> &b1, std::unique_ptr<Body> &b2) {
    auto p1 = b1->getPosition();
    auto p2 = b2->getPosition();
    Vector versor = (p1 - p2).versor();
    double distance = p1.distance(p2);

    // Formula for gravitational force. See
    // [gravity](https://en.wikipedia.org/wiki/Gravity).
    Vector gForce =
        -G * b1->getMass() * b2->getMass() / std::pow(distance, 2) * versor;
    b1->addForce(gForce);

    // TODO: Reimplement derivatives.

    // double X = b1->getPosition().x - b2->getPosition().x;
    // double Y = b1->getPosition().y - b2->getPosition().y;
    // double Xder = b1->getVelocity().x - b2->getVelocity().x;
    // double Yder = b1->getVelocity().y - b2->getVelocity().y;
    // double Xdd = b1->getAcceleration().x - b2->getAcceleration().x;
    // double Ydd = b1->getAcceleration().y - b2->getAcceleration().y;
    // Vector force;
    // Vector force_der;
    // Vector force_2der;

    // force.x = -G * (b1->getMass()) * (b2->getMass()) * X /
    //           std::pow(distance(b1, b2), 3);
    // force_der.x = -G * (b1->getMass()) * (b2->getMass()) *
    //               ((Xder * std::pow(distance(b1, b2), 2)) -
    //                1.5 * X * (2 * X * Xder + 2 * Y * Yder)) /
    //               std::pow(distance(b1, b2), 5);

    // force.y = -G * (b1->getMass()) * (b2->getMass()) * Y /
    //           std::pow(distance(b1, b2), 3);
    // force_der.y = -G * (b1->getMass()) * (b2->getMass()) *
    //               ((Yder * std::pow(distance(b1, b2), 2)) -
    //                1.5 * Y * (2 * X * Xder + 2 * Y * Yder)) /
    //               std::pow(distance(b1, b2), 5);
    // // mod
    // // calcolo force_2der spezzando i temrini che la compongono//lo so dovrei
    // // implementarla in un'altra funzione ma lo faccio qui solo per vedere se
    // // funziona
    // double Nx = Xder * (X * X + Y * Y) - 3 * X * (X * Xder + Y * Yder);
    // double Ny = Yder * (X * X + Y * Y) - 3 * Y * (X * Xder + Y * Yder);
    // double Nxprime = Xdd * (Y * Y - 2 * X * X) -
    //                  X * (4 * Xder * Xder + 3 * Yder * Yder) -
    //                  Y * (Xder * Yder + 3 * X * Ydd);
    // double Nyprime = Ydd * (X * X - 2 * Y * Y) -
    //                  Y * (4 * Yder * Yder + 3 * Xder * Xder) -
    //                  X * (Xder * Yder + 3 * Y * Xdd);
    // double D = std::pow(X * X + Y * Y, 2.5);
    // double Dprime = 5 * std::pow(X * X + Y * Y, 1.5) * (X * Xder + Y * Yder);

    // force_2der.x = -G * (b1->getMass()) * (b2->getMass()) *
    //                (Nxprime * D - Nx * Dprime) / (D * D);
    // force_2der.y = -G * (b1->getMass()) * (b2->getMass()) *
    //                (Nyprime * D - Ny * Dprime) / (D * D);

    // b1->addForce(force);
    // // Da implementare in EVOLVE
    // b1->setForce_derivUp(force_der);
    // // mod
    // b1->setForce2derivUp(force_2der);
  }
  // MODIFICHE//
  void evolve(std::unique_ptr<Body> &b1, double dt) {
    dt *= _timeScale;

    auto pos = b1->getPosition();
    auto vel = b1->getVelocity();

    auto acc = b1->getAcceleration();
    auto acc1 = b1->getAccDer();
    auto acc2 = b1->getAcc2der();

    // implementazione eulero

    auto newPosition = Vector{pos.x + vel.x * dt + 0.5 * acc.x * dt * dt +
                                  0.1666667 * acc1.x * dt * dt * dt +
                                  0.04166667 * acc2.x * dt * dt * dt * dt,
                              pos.y + vel.y * dt + 0.5 * acc.y * dt * dt +
                                  0.1666667 * acc1.y * dt * dt * dt +
                                  0.04166667 * acc2.y * dt * dt * dt * dt};
    // auto newPosition = Vector{pos.x + vel.x * dt + 0.5 * acc.x * dt *
    // dt+0.1666667 * acc1.x * dt * dt * dt,
    //                           pos.y + vel.y * dt + 0.5 * acc.y * dt *
    //                           dt+0.1666667 * acc1.y * dt * dt * dt};
    b1->setPosition(newPosition);

    vel.x = vel.x + acc.x * dt + 0.5 * acc1.x * dt * dt +
            0.1666667 * acc2.x * dt * dt * dt;
    vel.y = vel.y + acc.y * dt + 0.5 * acc1.y * dt * dt +
            0.1666667 * acc2.y * dt * dt * dt;

    // vel.x = vel.x + acc.x * dt + 0.5 * acc1.x * dt * dt;
    // vel.y = vel.y + acc.y * dt + 0.5 * acc1.y * dt * dt;
    b1->setVelocity(vel);
  }
};

#endif