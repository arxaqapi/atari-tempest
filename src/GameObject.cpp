/**
 * @file GameObject.cpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "GameObject.hpp"

#include <iostream>

GameObject::GameObject()
{
  std::cout << "GO init" << std::endl;
  run = 1;
}

GameObject::~GameObject()
{
  std::cout << "GO destr" << std::endl;
}

void
GameObject::trun()
{
  std::cout << "GO run" << std::endl;
  r_.clear();
  r_.draw();
  SDL_Delay(2000);
}

void
GameObject::stop()
{
  run = 0;
}