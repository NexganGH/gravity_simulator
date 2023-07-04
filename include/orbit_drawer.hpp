#ifndef ORBIT_DRAWER_H
#define ORBIT_DRAWER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "renderer.hpp"
#include "vector.hpp"

class OrbitDrawer {
 private:
  struct OrbitPoint {
    double time;
    Vector point;
  };
  std::vector<OrbitPoint> _orbitPoints;

  const double DELETE_AFTER_SECONDS = 50;

 public:
  void addPoint(Vector p, double time);

  void draw(std::unique_ptr<Renderer>& renderer, double time);
};

#endif