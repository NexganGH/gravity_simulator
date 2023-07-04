#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "../include/vector.hpp"

class GuiManager {
  tgui::Gui& _gui;

 public:
  GuiManager(tgui::Gui& gui) : _gui(gui) {}
  void create() {
    tgui::Button::Ptr play = tgui::Button::create(">");
    play->setPosition(50, 50);
    play->setSize(50, 50);
    play->setEnabled(true);
    _gui.add(play);

    auto _timeLabel = tgui::Label::create();
    _timeLabel->setText("Time elapsed: 0.0 years");
    _timeLabel->setPosition(50, 150);
    _timeLabel->setTextSize(18);
    auto renderer = _timeLabel->getSharedRenderer();
    renderer->setTextColor(tgui::Color::White);
    _gui.add(_timeLabel);

    auto _massInserter = tgui::EditBox::create();
    _massInserter->setText("2");

    _massInserter->setPosition(200, 200);

    _massInserter->onReturnKeyPress([=]() {
      // std::cout << _massInserter->getAbsolutePosition().y << "\n";
      // Must be converted to real (universe)'s coordinate

      tgui::Timer::scheduleCallback([=] { _gui.remove(_massInserter); });
      //_gui.remove(_massInserter);
    });

    _massInserter->onUnfocus([=]() { _gui.remove(_massInserter); });
    _gui.add(_massInserter);
  }
};

int main() {
  auto height = sf::VideoMode::getDesktopMode().height - 250;

  sf::RenderWindow window(sf::VideoMode(height, height), "Test",
                          sf::Style::Titlebar);

  auto gui = tgui::Gui{window};
  GuiManager manager(gui);

  manager.create();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      gui.handleEvent(event);
    }

    window.clear();

    gui.draw();

    window.display();
  }
}