#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include "configuration.hpp"
#include "SFML/Graphics.hpp"

#include <vector>
namespace gs {

/**
 * @return Default configurations.
*/
std::vector<std::shared_ptr<Configuration>> getConfigurations(
    sf::RenderWindow& window);

};
#endif