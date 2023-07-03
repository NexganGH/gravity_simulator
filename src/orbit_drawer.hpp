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
  void addPoint(Vector p, double time) {
    assert(time >= 0);
    _orbitPoints.push_back(OrbitPoint{time, p});
  }

  void draw(Renderer& renderer, double time) {
    auto toRemove = std::remove_if(
        _orbitPoints.begin(), _orbitPoints.end(), [&](OrbitPoint data) {
          return time - data.time > DELETE_AFTER_SECONDS;
        });
    _orbitPoints.erase(toRemove, _orbitPoints.end());

    for (auto data : _orbitPoints) {
      sf::CircleShape circle(2);
      circle.setFillColor(sf::Color::Green);
      circle.setPosition(data.point.toSfml());
      renderer.draw(circle);
    }
  }
};

#endif