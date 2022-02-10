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

class Entity
{
private:
  f32 x_pos_;
  f32 y_pos_;
  i32 health_;

public:
  Entity(/* args */);
  ~Entity();
};

#endif