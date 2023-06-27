#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <vector>

#include "physics_engine.hpp"

void handleReturnKey() {
  std::cout << "test";
}
class GuiManager {
 private:
  tgui::Gui& _gui;
  PhysicsEngine& _ph;

  tgui::Label::Ptr timeLabel;
  tgui::EditBox::Ptr _massInserter;

 public:
  GuiManager(tgui::Gui& gui, PhysicsEngine& ph) : _gui(gui), _ph(ph) {}

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


    timeLabel = tgui::Label::create();
    timeLabel->setText("Time elapsed: 0.0 years");
    timeLabel->setPosition(50, 150);
    timeLabel->setTextSize(18);
    auto renderer = timeLabel->getSharedRenderer();
    renderer->setTextColor(tgui::Color::White);
    _gui.add(timeLabel);

    
  }

  void setTimeElapsed(double timeElapsed) {
    timeLabel->setText("Time elapsed: " + std::to_string(timeElapsed) + " years");
  }

  void rightButtonClicked(sf::Event event) {
    _massInserter = tgui::EditBox::create();
    _massInserter->setText("2");
    _massInserter->setPosition(event.mouseButton.x, event.mouseButton.y);
    
    //editBox->on
    _gui.add(_massInserter);
  }

  void pressedEnter() {
    std::cout<<"grevissimo ";
    if(_massInserter)
      std::cout<<"greve";
  }
};

#endif