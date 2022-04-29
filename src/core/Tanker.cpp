/**
 * @file Tanker.cpp
 * @author massimo
 * @version 0.1
 * @date 2022-04-16
 *
 * @copyright Copyright (c) 2022
 */

#include "Tanker.hpp"

void
Tanker::render(SDLW::Renderer& renderer,
               const Map& map,
               const color& render_color) const
{
  if (!active_)
    return;

  const Band& band = map.getBand(band_num_);

  f32 fraction =
    utils::easeOutQuad(front_progression_, 1 - map.getFocal()) - map.getFocal();

  f32 size = 0.7 * map.getAvgBandWith();

  f32 outer_size = (size * (1 - fraction)) / 2;
  f32 inner_size = (size * (1 - fraction)) / 4;

  Vector2D u = { 1, 0 };
  Vector2D v = { 0, 1 };
  Vector2D position = band.getAxis() * fraction;

  Vector2D inner_left =
    band.getExterCenter() + (u * .7f * inner_size) + position;
  Vector2D inner_right =
    band.getExterCenter() + (u * (-.7f * inner_size)) + position;
  Vector2D inner_top = band.getExterCenter() + (v * inner_size) + position;
  Vector2D inner_bottom = band.getExterCenter() + (v * -inner_size) + position;
  Vector2D outer_left =
    band.getExterCenter() + (u * (.7f * outer_size)) + position;
  Vector2D outer_right =
    band.getExterCenter() + (u * (-.7f * outer_size)) + position;
  Vector2D outer_top = band.getExterCenter() + (v * outer_size) + position;
  Vector2D outer_bottom = band.getExterCenter() + (v * -outer_size) + position;

  renderer.SetRenderDrawColor(std::get<0>(render_color),
                              std::get<1>(render_color),
                              std::get<2>(render_color),
                              255);
  renderer.RenderDrawLineF(
    inner_left.getX(), inner_left.getY(), inner_top.getX(), inner_top.getY());
  renderer.RenderDrawLineF(
    inner_top.getX(), inner_top.getY(), inner_right.getX(), inner_right.getY());
  renderer.RenderDrawLineF(inner_right.getX(),
                           inner_right.getY(),
                           inner_bottom.getX(),
                           inner_bottom.getY());
  renderer.RenderDrawLineF(inner_bottom.getX(),
                           inner_bottom.getY(),
                           inner_left.getX(),
                           inner_left.getY());
  renderer.RenderDrawLineF(
    outer_left.getX(), outer_left.getY(), outer_top.getX(), outer_top.getY());
  renderer.RenderDrawLineF(
    outer_top.getX(), outer_top.getY(), outer_right.getX(), outer_right.getY());
  renderer.RenderDrawLineF(outer_right.getX(),
                           outer_right.getY(),
                           outer_bottom.getX(),
                           outer_bottom.getY());
  renderer.RenderDrawLineF(outer_bottom.getX(),
                           outer_bottom.getY(),
                           outer_left.getX(),
                           outer_left.getY());
  renderer.RenderDrawLineF(
    outer_top.getX(), outer_top.getY(), inner_left.getX(), inner_left.getY());
  renderer.RenderDrawLineF(
    outer_right.getX(), outer_right.getY(), inner_top.getX(), inner_top.getY());
  renderer.RenderDrawLineF(outer_bottom.getX(),
                           outer_bottom.getY(),
                           inner_right.getX(),
                           inner_right.getY());
  renderer.RenderDrawLineF(outer_left.getX(),
                           outer_left.getY(),
                           inner_bottom.getX(),
                           inner_bottom.getY());
}

void
Tanker::update(f64 delta, const Map& map)
{
  if (!active_)
    return;

  if (front_progression_ == 0) {
    split_ = true;
    active_ = false;
  }

  move(delta, map);
}
