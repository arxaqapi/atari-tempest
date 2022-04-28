/**
 * @file Spiker.cpp
 * @author massimo
 * @version 0.1
 * @date 2022-04-16
 *
 * @copyright Copyright (c) 2022
 */

#include "Spiker.hpp"

void
Spiker::render(SDLW::Renderer& renderer,
               const Map& map,
               const color& render_color) const
{
  if (!active_)
    return;

  f32 fraction =
    utils::easeOutQuad(front_progression_, 1 - map.getFocal()) - map.getFocal();

  const Band& band = map.getBand(band_num_);

  Vector2D position =
    band.getExterCenter().weightedMidPointTo(map.getOrigin(), fraction);

  renderer.SetRenderDrawColor(std::get<0>(render_color),
                              std::get<1>(render_color),
                              std::get<2>(render_color),
                              255);
  renderer.RenderDrawLineF(band.getInterCenter().getX(),
                           band.getInterCenter().getY(),
                           position.getX(),
                           position.getY());
}

void
Spiker::update(f64 delta, const Map& map)
{
  if (!active_)
    return;

  if (front_progression_ > 0.2)
    move(delta, map);
}

void
Spiker::hit()
{
  moving_direction_ = NONE;
  front_progression_ = std::min(1.0f, front_progression_ + .1f);
  if (front_progression_ == 1)
    deactivate();
}
