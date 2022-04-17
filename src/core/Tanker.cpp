//
// Created by massimo on 16/04/2022.
//

#include "Tanker.hpp"
#include <iostream>

Tanker::Tanker()
{
  deactivate();
}

void
Tanker::render(SDL_Renderer* renderer, const Map& map) const
{
  if (!active_)
    return;

  SDL_SetRenderDrawColor(renderer, 230, 0, 0, 255);

  // Draw rect for now...
  f32 fraction =
    utils::easeOutQuad(progress_, 1 - map.getFocal()) - map.getFocal();

  const Band& band = map.getBand(band_num_);

  Vector2D position = band.getExterCenter().vec_to(map.getOrigin()) * fraction + band.getExterCenter();

//    Vector2D position =
//      band.getExterCenter().weightedMidPointTo(map.getOrigin(), fraction);

  f32 size = 20 * (1 - fraction);

  SDL_FRect rect{ position.getX(), position.getY(), size, size };

  SDL_RenderFillRectF(renderer, &rect);
}

void
Tanker::update(f64 delta, const Map& map)
{
  if (!active_)
    return;

  if (progress_ == 0) {
    split_ = true;
    active_ = false;
  }

  move(delta, map);
}
