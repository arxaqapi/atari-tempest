/**
 * @file Flipper.cpp
 * @author massimo
 * @version 0.1
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2022
 */

#include "Flipper.hpp"

void
Flipper::render(SDLW::Renderer& renderer,
                const Map& map,
                const color& render_color) const
{
  if (!active_)
    return;

  const Band& band = map.getBand(band_num_);

  f32 fraction =
    utils::easeOutQuad(front_progression_, 1 - map.getFocal()) - map.getFocal();

  Vector2D left_bottom =
    band.getExterior().second.weightedMidPointTo(map.getOrigin(), fraction);
  Vector2D right_bottom =
    band.getExterior().first.weightedMidPointTo(map.getOrigin(), fraction);
  Vector2D orthogonal =
    left_bottom.vec_to(right_bottom).orthogonalVector().unit();

  f32 height = 0.2 * map.getAvgBandWith() * (1 - fraction);

  Vector2D left_top =
    left_bottom.weightedMidPointTo(right_bottom, .1) + (orthogonal * -height);
  Vector2D right_top =
    right_bottom.weightedMidPointTo(left_bottom, .1) + (orthogonal * -height);
  Vector2D left_inner = left_bottom.weightedMidPointTo(right_bottom, .2) +
                        (orthogonal * (-height / 2));
  Vector2D right_inner = right_bottom.weightedMidPointTo(left_bottom, .2) +
                         (orthogonal * (-height / 2));

  renderer.SetRenderDrawColor(std::get<0>(render_color),
                              std::get<1>(render_color),
                              std::get<2>(render_color),
                              255);
  renderer.RenderDrawLine(
    left_bottom.getX(), left_bottom.getY(), right_top.getX(), right_top.getY());
  renderer.RenderDrawLine(left_bottom.getX(),
                          left_bottom.getY(),
                          left_inner.getX(),
                          left_inner.getY());
  renderer.RenderDrawLine(
    left_inner.getX(), left_inner.getY(), left_top.getX(), left_top.getY());
  renderer.RenderDrawLine(
    right_bottom.getX(), right_bottom.getY(), left_top.getX(), left_top.getY());
  renderer.RenderDrawLine(right_bottom.getX(),
                          right_bottom.getY(),
                          right_inner.getX(),
                          right_inner.getY());
  renderer.RenderDrawLine(
    right_inner.getX(), right_inner.getY(), right_top.getX(), right_top.getY());
}

void
Flipper::update(f64 delta, const Map& map)
{
  if (!active_)
    return;

  // stuck at the end of the map, change direction
  if (band_change_direction_ == LEFT &&
      map.getLeftBandNum(band_num_) == band_num_)
    setBandChangeDirection(RIGHT);
  else if (band_change_direction_ == RIGHT &&
           map.getRightBandNum(band_num_) == band_num_)
    setBandChangeDirection(LEFT);
  // chasing player
  else if (front_progression_ == 0 && band_num_ < map.getSelectedBandNum())
    setBandChangeDirection(RIGHT);
  else if (front_progression_ == 0 && band_num_ > map.getSelectedBandNum())
    setBandChangeDirection(LEFT);

  setMovingDirection(band_change_direction_);
  move(delta, map);

  // move forward if not at the end of the band
  if (front_progression_ != 0) {
    setMovingDirection(FORWARD);
    move(delta, map);
  }
}
