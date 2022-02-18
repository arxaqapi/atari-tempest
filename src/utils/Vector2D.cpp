/**
 * @file Vector2D.cpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-02-17
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "Vector2D.hpp"
#include <cmath>

Vector2D::Vector2D(/* args */) {}

Vector2D::~Vector2D() {}

void
Vector2D::set(f32 x, f32 y)
{
  x_ = x;
  y_ = y;
}

f32
Vector2D::magnitude()
{
  return sqrtf32(x_ * x_ + y_ * y_);
}

Vector2D
Vector2D::vec_to(const Vector2D& point)
{
  return Vector2D{ this->x_ - point.x_, this->y_ - point.y_ };
}

Vector2D
Vector2D::unit_vector_to(const Vector2D& point)
{
  Vector2D to_point = this->vec_to(point);
  f32 m = to_point.magnitude();
  return Vector2D(to_point.x_ / m, to_point.y_ / m);
}