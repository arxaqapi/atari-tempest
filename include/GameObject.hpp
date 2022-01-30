#pragma once

#include "Renderer.hpp"


class GameObject
{
private:
    Renderer r_;
public:
    GameObject();
    ~GameObject();

    void trun();
    void stop();
  
    int run;
};

