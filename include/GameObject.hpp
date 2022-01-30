/**
 * @file GameObject.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef H_TEMPEST_GAME_INC_GAMEOBJECT_
#define H_TEMPEST_GAME_INC_GAMEOBJECT_

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

#endif