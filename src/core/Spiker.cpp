//
// Created by massimo on 16/04/2022.
//

#include "Spiker.hpp"
Spiker::Spiker() { deactivate(); }

void
Spiker::render(SDL_Renderer* renderer, const Map& map) const
{
  if (!active_)
    return;

  SDL_SetRenderDrawColor(renderer, 0, 250, 0, 255);

  f32 fraction =
    utils::easeOutQuad(progress_, 1 - map.getFocal()) - map.getFocal();

  const Band& band = map.getBand(band_num_);

  Vector2D position =
    band.getExterCenter().weightedMidPointTo(map.getOrigin(), fraction);

  SDL_RenderDrawLineF(renderer, band.getInterCenter().getX(), band.getInterCenter().getY(), position.getX(), position.getY());
}

void
Spiker::update(f64 delta, const Map& map)
{
  if (!active_)
    return;

  if (progress_ > 0.3)
    move(delta, map);
}
