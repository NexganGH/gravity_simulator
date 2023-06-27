#ifndef BODY_CONTAINER_H
#define BODY_CONTAINER

#include<vector>
#include "body.hpp"

class BodyContainer {

private:
  std::vector<std::unique_ptr<Body>> _bodies;

public:
  BodyContainer() {

  }

  void addBody(std::unique_ptr<Body> body) {
    _bodies.push_back(body);
  }
};

#endif