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
#include <tuple>

Band::Band(Vector2D exter_a, Vector2D exter_b, Vector2D origin, f32 focal)
  : exter_a_{ exter_a }
  , exter_b_{ exter_b }
  , inter_a_{ origin.weightedMidPointTo(exter_a, focal) }
  , inter_b_{ origin.weightedMidPointTo(exter_b, focal) }
  , exter_center_{ exter_a.weightedMidPointTo(exter_b, .5) }
  , inter_center_{ inter_a_.weightedMidPointTo(inter_b_, .5) }
  , axis_{ exter_center_.vec_to(inter_center_) }
  , unit_vector_{ axis_.unit() }
  , depth_{ axis_.magnitude() }
{}

void
Band::render(SDLW::Renderer& renderer,
             const color& standard_color,
             const color& accent_color) const
{
  if (is_selected_)
    renderer.SetRenderDrawColor(std::get<0>(accent_color),
                                std::get<1>(accent_color),
                                std::get<2>(accent_color),
                                255);
  else
    renderer.SetRenderDrawColor(std::get<0>(standard_color),
                                std::get<1>(standard_color),
                                std::get<2>(standard_color),
                                255);
  renderer.RenderDrawLineF(
    exter_a_.getX(), exter_a_.getY(), exter_b_.getX(), exter_b_.getY());
  renderer.RenderDrawLineF(
    exter_b_.getX(), exter_b_.getY(), inter_b_.getX(), inter_b_.getY());
  renderer.RenderDrawLineF(
    inter_b_.getX(), inter_b_.getY(), inter_a_.getX(), inter_a_.getY());
  renderer.RenderDrawLineF(
    inter_a_.getX(), inter_a_.getY(), exter_a_.getX(), exter_a_.getY());
}

const Vector2D&
Band::getExterCenter() const
{
  return exter_center_;
}
