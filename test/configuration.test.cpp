#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/body.hpp"
#include <SFML/Graphics.hpp>

#include "doctest.h"
#include "../include/configuration.hpp"
#include "../include/physics_engine.hpp"
#include "../include/renderer.hpp"

TEST_CASE("Testing configuration function"){
    SUBCASE("Testing the ad body function and createBody fucntion"){
        sf::RenderWindow window;
        Configuration conf("test configuration", 10,10, window)
        std::unique_ptr<Body> p1({0,0},{0,0},1);
        std::unique_ptr<Body> p2({1,1},{1,1},1);
         std::unique_ptr<Body> p3({2,2},{-1,-1},1);

        conf.addBody(p1);
        conf.adBody(p2);
        conf.addBody(p3);

        std::vector<std::unique_ptr<Body>> bodies=conf.createBodies();

        CHECK(bodies[0]->getPosition()==Vector{0,0});
        CHECK(bodies[0]->getVelocity()==Vector{0,0});
        CHECK(bodies[0]->getMass()== 1);

        CHECK(bodies[1]->getPosition()==Vector{1,1});
        CHECK(bodies[1]->getPosition()==Vector{1,1});
        CHECK(bodies[1]->getPosition()==1);

        CHECK(bodies[2]->getPosition()==Vector{2,2});
        CHECK(bodies[2]->getVelocity()==Vector{-1,-1});
        CHECK(bodies[2]->getMass()==1);        
    }

//createRenderer function isn't testes

    SUBCASE("Testing createPhysicsEngine function"){
        Configuration conf("test configuration", 10,10, window);
        std::unique_ptr<PhysicsEngine> ph=conf.createPhysicsEngine();
        CHECK(ph->getTimeScale==10);
    }


}