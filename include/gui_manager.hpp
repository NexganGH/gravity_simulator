#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "physics_engine.hpp"
#include "renderer.hpp"
#include "vector.hpp"
#include "simulation_state.hpp"

class GuiManager {
 private:
  tgui::Gui& _gui;
  SimulationState& _state;

  tgui::Label::Ptr _timeLabel;
  tgui::Label::Ptr _speed;

  // Body that is currently being created.
  std::unique_ptr<Body> _creatingBody;
  tgui::EditBox::Ptr _massInserter;

  

 public:
  GuiManager(tgui::Gui& gui, SimulationState& state);

  void createControlButtons();

  void setYearsElapsed(double timeElapsed, double secondsPerIteration);

  void rightButtonClicked(sf::Event event);

  void leftButtonClicked(sf::Event event);

  void drawArrow();
};

#endif