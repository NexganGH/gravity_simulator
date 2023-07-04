#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <vector>

#include "SFML/Graphics.hpp"
#include "body.hpp"
#include "configuration.hpp"
#include "renderer.hpp"

std::vector<std::shared_ptr<Configuration>> getConfigurations(
    sf::RenderWindow& window);

#endif