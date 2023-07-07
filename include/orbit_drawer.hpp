#ifndef ORBIT_DRAWER_H
#define ORBIT_DRAWER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "renderer.hpp"
#include "vector.hpp"

namespace gs {

/**
 * A class used to draw the orbit points of the planets in the screen.
 */
class OrbitDrawer {
 private:
  struct OrbitPoint {
    double time;
    Vector point;
  };
  std::vector<OrbitPoint> _orbitPoints;

  const double DELETE_AFTER_SECONDS = 50;

 public:
  /**
   * Adds a point to draw. The point will be deleted after a certain amount of
   * time.
   */
  void addPoint(Vector p, double time);

  /**
   * Draws the points according to the time in the program.
   *
   * @param renderer The renderer where to draw the points.
   * @param realTimeSeconds The realTimeSeconds since the beginning of the
   * program.
   */
  void draw(std::unique_ptr<Renderer>& renderer, double realTimeSeconds);

  /**
   * Deletes all the orbit points.
   */
  void reset();
};

};  // namespace gs

#endif