#ifndef ORBIT_DRAWER_H
#define ORBIT_DRAWER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "vector.hpp"
#include <iostream>
#include "renderer.hpp"

class OrbitDrawer {
  private:
    std::vector<Vector> _vectors;
  public:

    void addPoint(Vector p) {
      _vectors.push_back(p);
    }

    void draw(Renderer& renderer) {
      for (auto point : _vectors) {
        sf::CircleShape circle(2);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(point.toSfml());
        renderer.draw(circle); 
      }
    }

};

#endif