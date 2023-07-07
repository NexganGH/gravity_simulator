#include "gui_manager.hpp"

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "physics_engine.hpp"
#include "renderer.hpp"
#include "simulation_state.hpp"
#include "vector.hpp"

namespace gs {

GuiManager::GuiManager(
    sf::RenderWindow& window, SimulationState& state,
    std::vector<std::shared_ptr<Configuration>> configurations)
    : _gui(tgui::Gui(window)),
      _state(state),
      _availableConfigurations(configurations) {}

void GuiManager::setup() {
  createPlayButton();
  createResetButton();
  createLabels();
  createConfigurationList();
}

void GuiManager::updateValues(double timeElapsed, double simulationSpeed) {
  _timeLabel->setText("Time elapsed: " + std::to_string(timeElapsed) +
                      " years");

  _speed->setText("Simulation speed: " +
                  std::to_string(simulationSpeed / 86400) + " days/s");
}

void GuiManager::handleEvent(sf::Event event) {
  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Right) {
      rightButtonClicked(event);
    } else if (event.mouseButton.button == sf::Mouse::Left) {
      leftButtonClicked(event);
    }
  }

  _gui.handleEvent(event);
}

void GuiManager::rightButtonClicked(sf::Event event) {
  _massInserter = tgui::EditBox::create();
  _massInserter->setText("2");

  _massInserter->setPosition((double)event.mouseButton.x,
                             (double)event.mouseButton.y);

  _massInserter->onReturnKeyPress([=]() {
    Vector pos = {_massInserter->getPosition().x,
                  _massInserter->getPosition().y};
    // Must be converted to real (universe)'s coordinate
    Vector realPos = _state.getRenderer()->screenToReal(pos);

    auto massInEarthUnits = _massInserter->getText().toFloat();

    if (massInEarthUnits > 0 && massInEarthUnits < 1E15) {
      _creatingBody = std::make_unique<Planet>(
          realPos, Vector{0, 0},
          _massInserter->getText().toFloat() * 5.9722E24);
        }
    _massInserter->onUnfocus.disconnectAll();
    _gui.remove(_massInserter);
  });

  _massInserter->onUnfocus([=]() { _gui.remove(_massInserter); });
  _gui.add(_massInserter);
}

void GuiManager::leftButtonClicked(sf::Event event) {
  if (_creatingBody) {
    Vector mousePos{(double)event.mouseButton.x, (double)event.mouseButton.y};
    mousePos = _state.getRenderer()->screenToReal(mousePos);
    auto velocityVersor = (mousePos - _creatingBody->getPosition()).versor();
    _creatingBody->setVelocity(velocityVersor * 30E3);
    _state.getBodies().push_back(std::move(_creatingBody));
  }
}

void GuiManager::draw() {
  _gui.draw();

  if (_creatingBody) {
    auto& renderer = _state.getRenderer();

    auto p1 = renderer->realToScreen(_creatingBody->getPosition().toSfml());
    auto p2 = renderer->getMousePosition();

    sf::VertexArray line(sf::Lines, 2);
    line[0].position = p1;
    line[0].color = sf::Color::White;
    line[1].position = p2;
    line[1].color = sf::Color::White;

    renderer->drawGui(line);
  }

  _orbitDrawer.draw(_state.getRenderer(),
                    _state.getPhysicsEngine()->getRealSecondsElapsed());
}

void GuiManager::addOrbitPoint(Vector p, double time) {
  _orbitDrawer.addPoint(p, time);
}

void GuiManager::createPlayButton() {
  _playBtn = tgui::Button::create(">");
  _playBtn->setPosition(50, 25);
  _playBtn->setSize(50, 50);
  _playBtn->onPress.connect([=]() {
    auto& ph = _state.getPhysicsEngine();
    ph->toggleRunning();

    // Toggle between the pause and the play symbol.
    _playBtn->setText(ph->isRunning() ? "||" : ">");
  });
  _gui.add(_playBtn);
}

void GuiManager::createResetButton() {
  auto reset = tgui::Button::create("reset");
  reset->setPosition(100, 25);
  reset->setSize(50, 50);
  reset->setEnabled(true);
  reset->onPress.connect([=]() {
    _orbitDrawer.reset();
    this->_state.reset();
    _playBtn->setText(">");
  });
  _gui.add(reset);
}

void GuiManager::createLabels() {
  _timeLabel = tgui::Label::create();
  _timeLabel->setText("Time elapsed: 0.0 years");
  _timeLabel->setPosition(50, 75);
  _timeLabel->setTextSize(18);
  auto renderer = _timeLabel->getSharedRenderer();
  renderer->setTextColor(tgui::Color::White);
  _gui.add(_timeLabel);

  _speed = tgui::Label::create();
  _speed->setText("Simulation speed: - days/s");
  _speed->setPosition(50, 100);
  _speed->setTextSize(18);
  _gui.add(_speed);
}

void GuiManager::createConfigurationList() {
  auto confBoxList = tgui::ListBox::create();
  confBoxList->setPosition(50, 125);
  auto lRenderer = confBoxList->getRenderer();
  lRenderer->setTextColor(sf::Color::Black);

  int id{0};
  for (auto& conf : _availableConfigurations) {
    confBoxList->addItem(conf->getName(), std::to_string(id));
    ++id;
  }

  confBoxList->onItemSelect([=]() {
    auto item = confBoxList->getSelectedItemId();
    this->_state.reset(this->_availableConfigurations[item.toInt()]);
    _state.reset();
    _orbitDrawer.reset();
  });

  _gui.add(confBoxList);
}
};  // namespace gs