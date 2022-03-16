/**
 * @file Band.cpp
 * @author massimo
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "Band.hpp"

Band::Band(Vector2D exter_a,
           Vector2D exter_b,
           Vector2D inter_a,
           Vector2D inter_b)
  : exter_a_{ exter_a }
  , exter_b_{ exter_b }
  , inter_a_{ inter_a }
  , inter_b_{ inter_b }
  , exter_center_{ calcCenter(exter_a, exter_b) }
  , inter_center_{ calcCenter(inter_a, inter_b) }
  , unit_vector_{ exter_a.unit() }
  , depth_{ exter_center_.vec_to(inter_center_).magnitude() }
{}

Vector2D
Band::calcCenter(const Vector2D& vec1, const Vector2D& vec2)
{
  return { (vec1.getX() + vec2.getX()) / 2, (vec1.getY() + vec2.getY()) / 2 };
}

Vector2D
Band::calcPosition(f32 depth) const
{
  Vector2D p{ -unit_vector_.getY() * depth, unit_vector_.getX() * depth };
  return p + exter_center_;
}

void
Band::render(SDL_Renderer* r) const
{
  if (is_selected_)
    SDL_SetRenderDrawColor(r, 255, 255, 0, 255);
  else
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
  SDL_RenderDrawLineF(
    r, exter_a_.getX(), exter_a_.getY(), exter_b_.getX(), exter_b_.getY());
  SDL_RenderDrawLineF(
    r, exter_b_.getX(), exter_b_.getY(), inter_b_.getX(), inter_b_.getY());
  SDL_RenderDrawLineF(
    r, inter_b_.getX(), inter_b_.getY(), inter_a_.getX(), inter_a_.getY());
  SDL_RenderDrawLineF(
    r, inter_a_.getX(), inter_a_.getY(), exter_a_.getX(), exter_a_.getY());
}
