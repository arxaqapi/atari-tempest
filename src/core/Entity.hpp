/**
 * @file Entity.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-02-10
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef H_TEMPEST_GAME_INC_ENTITY_
#define H_TEMPEST_GAME_INC_ENTITY_

#include "../utils/types.hpp"

#include "../utils/Vector2D.hpp"
class Entity
{
private:
  Vector2D position_;
  i32 health_ = 0;

public:
  Entity(/* args */);
  ~Entity();
};

#endif