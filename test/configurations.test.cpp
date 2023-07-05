#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <SFML/Graphics.hpp>

#include "doctest.h"
#include "configurations.hpp"

TEST_CASE("Testing getConfigurations function"){ 
const float EARTH_SUN_DISTANCE = 149597870700;
const float EARTH_SPEED = 30.24E3;
const float EARTH_MASS = 5.9722E24;
const float SUN_MASS = 1.98855E30;

const float MERCURY_AFELIO=69.8E9;
const float MERCURY_AFELIO_SPEED=39.0E3;
const float MERCURY_MASS= 0.055*EARTH_MASS;

const float MOON_AFELIO=405500E3;
const float MOON_AFELIO_SPEED=0.970E3;
const float MOON_MASS= 7.3476E22;

const float VENUS_AFELIO=109.8E9;
const float VENUS_AFELIO_SPEED=34.78E3;
const float VENUS_MASS= 0.815*EARTH_MASS;

const float MARS_AFELIO=249.261E9;
const float MARS_AFELIO_SPEED=21.97E3;
const float MARS_MASS= 0.1*EARTH_MASS;

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
    CHECK(bodies[4]->getPosition()==Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2- MARS_AFELIO,
             height / 2});
    CHECK(bodies[5]->getPosition()==Vector{0.5 * 1E5 + MARS_AFELIO + MARS_AFELIO / 2+EARTH_SUN_DISTANCE+MOON_AFELIO,
             height / 2});

    CHECK(bodies[0]->getVelocity()==Vector{0, 0});
    CHECK(bodies[1]->getVelocity()==Vector{0, -EARTH_SPEED});
    CHECK(bodies[2]->getVelocity()==Vector{0, MERCURY_AFELIO_SPEED});
    CHECK(bodies[3]->getVelocity()==Vector{0, VENUS_AFELIO_SPEED});
    CHECK(bodies[4]->getVelocity()==Vector{0, MARS_AFELIO_SPEED});
    CHECK(bodies[5]->getVelocity()==Vector{0, -MOON_AFELIO_SPEED-EARTH_SPEED});



}
