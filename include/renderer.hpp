#ifndef DISTANCE_CALCULATOR_H
#define DISTANCE_CALCULATOR_H

#include <bits/stdc++.h>

#include <SFML/Graphics.hpp>

#include "body.hpp"

namespace gs {

/**
 * Class used to properly calculate the distance between two objects, in order
 * to render them properly on the screen.
 */
class Renderer {
 private:
  sf::RenderWindow& _window;

  // Example: if scale = 2 => Real distance between two objects is
  // (screenDistance)*2 (in meters) If scale = 1, the 1 pixel = 1 meter.
  double _scale;

  double realToScreen(double real);
  double screenToReal(double screen);

 public:
  Renderer(sf::RenderWindow& window, double scale);

  /**
   * Creates the Renderer according to the given universeWidth
   *
   * @param window The SFML's RenderWindow.
   * @param universeWidth The width of the universe in meters, so that bodies
   * can be scaled accordingly.
   */
  static std::unique_ptr<Renderer> fromUniverseWidth(sf::RenderWindow& window,
                                                     double universeWidth);

  /**
   * @returns The width of the universe in meters.
   */
  double getUniverseWidth();
  /**
   * @returns The height of the universe height.
   */
  double getUniverseHeight();

  /**
   * Draw the body. The position is converted automatically to pixels - from
   * meters.
   *
   * @param body The body to draw.
   */
  void draw(std::unique_ptr<Body>& body);

  /**
   * Draw the shape on screen. The position is converted automatically to pixels
   * - from meters.
   *
   * @param shape The shape to draw.
   */
  void draw(sf::Shape& shape);

  /**
   * Draw the shape on screen for GUI. The shape is already in pixels.
   */
  void drawGui(sf::VertexArray& shape);

  /**
   * Convers the vector from screen (pixel) coordinates to real (meters)
   * coordinates.
   *
   * @param screen The vector in screen coordinates to convert.
   * @return The same vector in universe coordinates.
   */
  Vector screenToReal(Vector screen);

  /**
   * Converts the vector from real (pixel) coordinates to screen (meters)
   * coordinates.
   *
   * @param real The vector in universe coordinates to convert.
   * @return The same vector in real coordinates.
   */
  sf::Vector2f realToScreen(sf::Vector2f real);

  /**
   * @return The nouse positon - in screen coordinates (pixels).
   */
  sf::Vector2f getMousePosition();

  // Copy constructor.
  Renderer(const Renderer& renderer);
};

};  // namespace gs

#endif
