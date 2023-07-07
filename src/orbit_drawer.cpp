#include "orbit_drawer.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "renderer.hpp"
#include "vector.hpp"

namespace gs {

void OrbitDrawer::addPoint(Vector p, double time) {
  if (time < 0) throw std::invalid_argument("time must be >= 0.");
  _orbitPoints.push_back(OrbitPoint{time, p});
}

void OrbitDrawer::draw(std::unique_ptr<Renderer>& renderer, double time) {
  auto toRemove = std::remove_if(
      _orbitPoints.begin(), _orbitPoints.end(),
      [&](OrbitPoint data) { return time - data.time > DELETE_AFTER_SECONDS; });
  _orbitPoints.erase(toRemove, _orbitPoints.end());

  for (auto data : _orbitPoints) {
    sf::CircleShape circle(2);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(data.point.toSfml());
    renderer->draw(circle);
  }
}

void OrbitDrawer::reset() { _orbitPoints.clear(); }

};  // namespace gs