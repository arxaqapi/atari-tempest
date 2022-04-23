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
#include <utility>

class Vector2D
{

private:
  f32 x_ = 0.f;
  f32 y_ = 0.f;

public:
  Vector2D() = default;
  Vector2D(const Vector2D& vector) = default;
  Vector2D(f32 x, f32 y);
  ~Vector2D() = default;

  void set(f32 x, f32 y);
  f32 getX() const;
  f32 getY() const;

  f32 magnitude() const;
  Vector2D vec_to(const Vector2D& point) const;
  /**
   * @brief Computes the unit vector from the actual position
   * to the position of the parameter point
   *
   * @param point the point to reach
   * @return Vector2D The direction vector
   */
  Vector2D unit_vector_to(const Vector2D& point) const;

  Vector2D unit() const;

  inline Vector2D weightedMidPointTo(const Vector2D& point, f32 weight) const
  {
    return { (1 - weight) * x_ + weight * point.x_,
             (1 - weight) * y_ + weight * point.y_ };
  }

  inline Vector2D orthogonalVector() const { return { y_, -x_ }; };

  Vector2D operator+(const Vector2D& vector) const;

  Vector2D operator*(f32 lambda) const;
};

#endif