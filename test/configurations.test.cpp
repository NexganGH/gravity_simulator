#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "body.hpp"
#include <SFML/Graphics.hpp>

#include "doctest.h"
#include "configurations.hpp"
#include "configuration.hpp"

TEST_CASE("Testing getConfigurations function"){ 
    sf::RenderWindow window;
    std::vector<std::shared_ptr<Configuration>> a= getConfigurations(window);
    std::shared_ptr<Configuration> b= a[0];
    std::vector<std::unique_ptr<Body>> bodies=b->createBodies();
    
    CHECK(bodies[0]->getMass()==SUN_MASS);
    CHECK(bodies[1]->getMass()==EARTH_MASS);
    CHECK(bodies[2]->getMass()==0.55*EARTH_MASS);
    CHECK(bodies[3]->getMass()==0.815*EARTH_MASS);
    CHECK(bodies[4]->getMass()==0.1*EARTH_MASS);
    CHECK(bodies[5]->getMass()==MOON_MASS);
}