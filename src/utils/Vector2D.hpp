/**
 * @file Vector2D.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-02-17
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef H_TEMPEST_GAME_INC_VECTOR_2D_
#define H_TEMPEST_GAME_INC_VECTOR_2D_

#include "types.hpp"

class Vector2D
{
private:
  f32 x_ = 0.f;
  f32 y_ = 0.f;

public:
  Vector2D();
  Vector2D(f32 x, f32 y)
    : x_(x)
    , y_(y){};
  ~Vector2D();

  void set(f32 x, f32 y);

  f32 magnitude();
  Vector2D vec_to(const Vector2D& point);
  /**
   * @brief Computes the unit vector from the actual position
   * to the position of the parameter point
   *
   * @param point the point to reach
   * @return Vector2D The direction vector
   */
  Vector2D unit_vector_to(const Vector2D& point);
};

using Position = Vector2D;

#endif