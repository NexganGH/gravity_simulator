#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "physics_engine.hpp"
#include <iostream>
#include <vector>

class GuiManager {
 private:
  tgui::Gui& _gui;
  PhysicsEngine& _ph;

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
  }

  void rightButtonClicked(sf::Event event) {
    auto listBox = tgui::ListBox::create();
    // listBox->setRenderer(theme.getRenderer("ListBox"));
    listBox->setSize(120, 30);
    listBox->setItemHeight(24);
    listBox->setPosition(event.mouseButton.x, event.mouseButton.y);
    listBox->addItem("Item 1");
    listBox->setEnabled(true);
    listBox->onItemSelect.connect([&]() { std::cout << "test"; });
    _gui.add(listBox);
  }
};

#endif