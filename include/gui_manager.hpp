#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H


#include "simulation_state.hpp"
#include "orbit_drawer.hpp"

#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <cmath>
#include <iostream>
#include <vector>

namespace gs {

class GuiManager {
 private:
  tgui::Gui _gui;
  SimulationState& _state;
  OrbitDrawer _orbitDrawer;

  tgui::Label::Ptr _timeLabel;
  tgui::Label::Ptr _speed;

  // Body that is currently being created.
  std::unique_ptr<Body> _creatingBody;
  tgui::EditBox::Ptr _massInserter;

  void rightButtonClicked(sf::Event event);

  void leftButtonClicked(sf::Event event);

 public:
  GuiManager(sf::RenderWindow& window, SimulationState& state);

  /**
   * Setup the gui to create the control buttons - play, pause, and similar.
   */
  void setup();

  /**
   * Update the GUI to show the new values.
   *
   * @param yearsElapsed The simulation years elapsed from the start.
   * @param simulationSpeed The speed of the simulation, in simulation seconds
   * per real seconds.
   */
  void updateValues(double yearsElapsed, double simulationSpeed);

  /**
   * Call when the button
   */
  void handleEvent(sf::Event event);

  /**
   * Draw the gui.
  */
  void draw();

  void addPoint(Vector p, double time);
};

};

#endif