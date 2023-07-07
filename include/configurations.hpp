#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <vector>

#include "SFML/Graphics.hpp"
#include "configuration.hpp"
namespace gs {

/**
 * @return Default configurations.
 */
std::vector<std::shared_ptr<Configuration>> getConfigurations(
    sf::RenderWindow& window);

};  // namespace gs
#endif