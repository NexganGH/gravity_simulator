#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <vector>

#include "physics_engine.hpp"

void handleReturnKey() { std::cout << "test"; }
class GuiManager {
 private:
  tgui::Gui& _gui;
  PhysicsEngine& _ph;

  tgui::Label::Ptr _timeLabel;
  std::vector<std::unique_ptr<Body>>& _bodies;

  // Body that is currently being created.
  std::unique_ptr<Body> _creatingBody;

 public:
  GuiManager(tgui::Gui& gui, PhysicsEngine& ph,
             std::vector<std::unique_ptr<Body>>& bodies)
      : _gui(gui), _ph(ph), _bodies(bodies) {}

  void controlButtons() {
    tgui::Button::Ptr play = tgui::Button::create(">");
    play->setPosition(50, 50);
    play->setSize(50, 50);
    play->setEnabled(true);
    play->onPress.connect([=]() {
      _ph.toggleRunning();

      play->setText(_ph.isRunning() ? "||" : ">");
    });
    _gui.add(play);

    _timeLabel = tgui::Label::create();
    _timeLabel->setText("Time elapsed: 0.0 years");
    _timeLabel->setPosition(50, 150);
    _timeLabel->setTextSize(18);
    auto renderer = _timeLabel->getSharedRenderer();
    renderer->setTextColor(tgui::Color::White);
    _gui.add(_timeLabel);
  }

  void setTimeElapsed(double timeElapsed) {
    _timeLabel->setText("Time elapsed: " + std::to_string(timeElapsed) +
                        " years");
  }

  void rightButtonClicked(sf::Event event) {
    auto _massInserter = tgui::EditBox::create();
    _massInserter->setText("2");
    _massInserter->setPosition(event.mouseButton.x, event.mouseButton.y);

    _massInserter->onReturnKeyPress([=]() {
      _creatingBody = std::make_unique<Planet>(
          _massInserter->getPosition().x, _massInserter->getPosition().y,
          _massInserter->getText().toFloat() * 5.9722E24);
          //this.

    });

    _massInserter->onUnfocus([=]() { _gui.remove(_massInserter); });
    _gui.add(_massInserter);
  }
};

#endif