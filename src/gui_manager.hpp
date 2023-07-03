#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "physics_engine.hpp"
#include "renderer.hpp"
#include "vector.hpp"

class GuiManager {
 private:
  tgui::Gui& _gui;
  PhysicsEngine& _ph;

  tgui::Label::Ptr _timeLabel;
  tgui::Label::Ptr _speed;
  std::vector<std::unique_ptr<Body>>& _bodies;
  Renderer& _renderer;
  //added
 const std::vector<Cuple_Vector> _initial_states;

  // Body that is currently being created.
  std::unique_ptr<Body> _creatingBody;
  tgui::EditBox::Ptr _massInserter;

 public:
 //added modified constructor
  GuiManager(tgui::Gui& gui, PhysicsEngine& ph,
             std::vector<std::unique_ptr<Body>>& bodies, Renderer& renderer, const std::vector<Cuple_Vector> initialStates)
      : _gui(gui), _ph(ph), _bodies(bodies), _renderer(renderer), _initial_states(initialStates) {}

  void createControlButtons() {
    tgui::Button::Ptr play = tgui::Button::create(">");
    play->setPosition(50, 25);
    play->setSize(50, 50);
    play->setEnabled(true);
    play->onPress.connect([=]() {
      _ph.toggleRunning();

      play->setText(_ph.isRunning() ? "||" : ">");
    });
    _gui.add(play);

    tgui::Button::Ptr reset = tgui::Button::create("reset");
    reset->setPosition(100, 25);
    reset->setSize(50, 50);
    reset->setEnabled(true);
    reset->onPress.connect([=]() {
      if (_ph.isRunning()) {
        _ph.toggleRunning();
        play->setText(">");
      }
      _ph.resetTimeElapsed();
//added inserisco le posizioni salvate iniziali nei paineti che si trovano in _bodies
      for(int i{0}; i<_initial_states.size(); ++i){
        (_bodies[i])->setPosition((_initial_states[i]).pos);
        (_bodies[i])->setPosition((_initial_states[i]).vel);
      }

    });
    _gui.add(reset);

    _timeLabel = tgui::Label::create();
    _timeLabel->setText("Time elapsed: 0.0 years");
    _timeLabel->setPosition(50, 75);
    _timeLabel->setTextSize(18);
    auto renderer = _timeLabel->getSharedRenderer();
    renderer->setTextColor(tgui::Color::White);
    _gui.add(_timeLabel);

    _speed = tgui::Label::create();
    _speed->setText("Simulation speed: - days/s");
    _speed->setPosition(50, 125);
    _speed->setTextSize(18);
    _gui.add(_speed);
  }

  void setYearsElapsed(double timeElapsed, double secondsPerIteration) {
    _timeLabel->setText("Time elapsed: " + std::to_string(timeElapsed) +
                        " years");

    _speed->setText("Simulation speed: " +
                    std::to_string(secondsPerIteration / 86400) + " days/s");
  }

  void rightButtonClicked(sf::Event event) {
    _massInserter = tgui::EditBox::create();
    _massInserter->setText("2");

    _massInserter->setPosition((double)event.mouseButton.x,
                               (double)event.mouseButton.y);

    _massInserter->onReturnKeyPress([=]() {
      // std::cout << _massInserter->getAbsolutePosition().y << "\n";
      Vector pos = {_massInserter->getPosition().x,
                    _massInserter->getPosition().y};
      // Must be converted to real (universe)'s coordinate
      Vector realPos = _renderer.screenToReal(pos);

      _creatingBody = std::make_unique<Planet>(
          realPos, Vector{0, 0},
          _massInserter->getText().toFloat() * 5.9722E24);
      _massInserter->onUnfocus.disconnectAll();
      _gui.remove(_massInserter);
      //_gui.remove(_massInserter);
    });

    _massInserter->onUnfocus([=]() { _gui.remove(_massInserter); });
    _gui.add(_massInserter);
  }

  void leftButtonClicked(sf::Event event) {
    if (_creatingBody) {
      Vector mousePos{(double)event.mouseButton.x, (double)event.mouseButton.y};
      mousePos = _renderer.screenToReal(mousePos);
      auto velocityVersor = (mousePos - _creatingBody->getPosition()) /
                            (mousePos - _creatingBody->getPosition()).norm();
      _creatingBody->setVelocity(velocityVersor * 30E3);
      _bodies.push_back(std::move(_creatingBody));
    }
  }

  void drawArrow() {
    if (_creatingBody) {
      auto p1 = _renderer.realToScreen(_creatingBody->getPosition().toSfml());
      auto p2 = _renderer.getMousePosition();

      sf::VertexArray line(sf::Lines, 2);
      line[0].position = p1;
      line[0].color = sf::Color::White;
      line[1].position = p2;
      line[1].color = sf::Color::White;

      _renderer.drawGui(line);
    }
  }
};

#endif