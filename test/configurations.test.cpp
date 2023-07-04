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
    auto height = 2*MARS_AFELIO  + EARTH_SUN_DISTANCE;
    
    CHECK(bodies[0]->getMass()==SUN_MASS);
    CHECK(bodies[1]->getMass()==EARTH_MASS);
    CHECK(bodies[2]->getMass()==MERCURY_MASS);
    CHECK(bodies[3]->getMass()==VENUS_MASS);
    CHECK(bodies[4]->getMass()==MARS_MASS);
    CHECK(bodies[5]->getMass()==MOON_MASS);

    CHECK(bodies[0]->getPosition()==Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2,
             height / 2});
    CHECK(bodies[1]->getPosition()==Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2+EARTH_SUN_DISTANCE,
             height / 2});
    CHECK(bodies[2]->getPosition()==Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2- MERCURY_AFELIO,
             height / 2});
    CHECK(bodies[3]->getPosition()==Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2- VENUS_AFELIO,
             height / 2});
    CHECK(bodies[4]->getPosition()==Vector{});
    CHECK(bodies[5]->getPosition()==Vector{});


}