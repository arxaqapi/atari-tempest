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

  inline static Vector2D between(const Vector2D& vec1,
                                 const Vector2D& vec2,
                                 f32 percentage)
  {
    return { (vec1.getX() + vec2.getX()) * percentage,
             (vec1.getY() + vec2.getY()) * percentage };
  }

  inline static Vector2D center(const Vector2D& vec1, const Vector2D& vec2)
  {
    return between(vec1, vec2, 0.5);
  }

  Vector2D operator+(const Vector2D& vector) const;
};

using Position = Vector2D;

#endif