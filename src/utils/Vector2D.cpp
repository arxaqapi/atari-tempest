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

Vector2D::Vector2D(f32 x, f32 y)
  : x_(x)
  , y_(y)
{}

void
Vector2D::set(f32 x, f32 y)
{
  x_ = x;
  y_ = y;
}

f32
Vector2D::magnitude() const
{
  return sqrtf32(x_ * x_ + y_ * y_);
}

Vector2D
Vector2D::vec_to(const Vector2D& point) const
{
  return { point.x_ - x_, point.y_ - y_ };
}

Vector2D
Vector2D::unit_vector_to(const Vector2D& point) const
{
  return vec_to(point).unit();
}

f32
Vector2D::getX() const
{
  return x_;
}

f32
Vector2D::getY() const
{
  return y_;
}

Vector2D
Vector2D::unit() const
{
  auto mag = magnitude();
  return { x_ / mag, y_ / mag };
}
Vector2D
Vector2D::operator+(const Vector2D& vector) const
{
  return { x_ + vector.x_, y_ + vector.y_ };
}

Vector2D
Vector2D::operator*(f32 lambda) const
{
  return { x_ * lambda, y_ * lambda};
}
