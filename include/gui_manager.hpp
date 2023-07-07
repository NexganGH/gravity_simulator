#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <vector>

#include "orbit_drawer.hpp"
#include "simulation_state.hpp"

namespace gs {

/**
 * A class used to setup and manage the GUI.
 */
class GuiManager {
 private:
  tgui::Gui _gui;
  SimulationState& _state;
  OrbitDrawer _orbitDrawer;
  std::vector<std::shared_ptr<Configuration>> _availableConfigurations;

  tgui::Label::Ptr _timeLabel;
  tgui::Label::Ptr _speed;

  tgui::Button::Ptr _playBtn;
  // Body that is currently being created.
  std::unique_ptr<Body> _creatingBody;
  tgui::EditBox::Ptr _massInserter;

  /**
   * Must be called to handle a right click event.
   *
   * @param event The SFML event.
   */
  void rightButtonClicked(sf::Event event);

  /**
   * Must be called to handle a left click event.
   *
   * @param event The SFML event.
   */
  void leftButtonClicked(sf::Event event);

  // These are all internal functions used to create the GUI. Names are
  // self-explanatory.
  void createPlayButton();
  void createResetButton();
  void createLabels();
  void createConfigurationList();

 public:
  GuiManager(sf::RenderWindow& window, SimulationState& state,
             std::vector<std::shared_ptr<Configuration>> configurations);

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

  /**
   * Add an orbit point to the GUI
   *
   * @param p The point being added.
   * @param time The time at which this orbit point was registered.
   */
  void addOrbitPoint(Vector p, double time);
};

};  // namespace gs

#endif