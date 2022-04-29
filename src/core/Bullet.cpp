/**
 * @file Bullet.cpp
 * @author massimo
 * @version 0.1
 * @date 2022-03-24
 *
 * @copyright Copyright (c) 2022
 */

#include "Bullet.hpp"

void
Bullet::update(f64 delta, const Map& map)
{
  if (!active_)
    return;

  if ((moving_direction_ == BACKWARD && front_progression_ == 1) ||
      (moving_direction_ == FORWARD && front_progression_ == 0))
    active_ = false;

  move(delta, map);
}

void
Bullet::render(SDLW::Renderer& renderer,
               const Map& map,
               const color& render_color) const
{
  if (!active_)
    return;

  f32 fraction =
    utils::easeOutQuad(front_progression_, 1 - map.getFocal()) - map.getFocal();

  const Band& band = map.getBand(band_num_);

  f32 size = 0.1 * map.getAvgBandWith() * (1 - fraction);

  Vector2D position = band.getAxis() * fraction;
  Vector2D orthogonal = band.getUnitVector().orthogonalVector();
  Vector2D left = band.getExterCenter() + (orthogonal * (size / 2)) + position;
  Vector2D right =
    band.getExterCenter() + (orthogonal * (-size / 2)) + position;
  Vector2D top =
    band.getExterCenter() + (band.getUnitVector() * (size / 2)) + position;
  Vector2D bottom =
    band.getExterCenter() + (band.getUnitVector() * (-size / 2)) + position;

  renderer.SetRenderDrawColor(std::get<0>(render_color),
                              std::get<1>(render_color),
                              std::get<2>(render_color),
                              255);
  renderer.RenderDrawLineF(left.getX(), left.getY(), top.getX(), top.getY());
  renderer.RenderDrawLineF(top.getX(), top.getY(), right.getX(), right.getY());
  renderer.RenderDrawLineF(
    right.getX(), right.getY(), bottom.getX(), bottom.getY());
  renderer.RenderDrawLineF(
    bottom.getX(), bottom.getY(), left.getX(), left.getY());
}
