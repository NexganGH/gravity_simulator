#ifndef RESET_H
#define RESET_H

#include<vector>
#include "physics_engine.hpp"
#include "body.hpp"
#include "renderer.hpp"

/**
 * Class used to reset the simulation.
 */
class Reset {
  Reset(PhysicsEngine& ph, std::vector<std::unique_ptr<Body>>& bodies,
        Renderer& renderer) {}
};

#endif RESET_H