//
// Created by massimo on 23/03/2022.
//

#include "Flipper.hpp"
#include "../utils/Utils.hpp"
#include <iostream>

Flipper::Flipper()
{
  deactivate();
}

void
Flipper::render(SDL_Renderer* renderer, const Map& map) const
{
  if (!active_)
    return;

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  const Band& band = map.getBand(band_num_);

  f32 fraction =
    utils::easeOutQuad(progress_, 1 - map.getFocal()) - map.getFocal();

  Vector2D right_bottom =
    band.getExterior().first.weightedMidPointTo(map.getOrigin(), fraction);
  Vector2D left_bottom =
    band.getExterior().second.weightedMidPointTo(map.getOrigin(), fraction);

  Vector2D orthogonal =
    left_bottom.vec_to(right_bottom).orthogonalVector().unit();

  f32 height = 20 * (1 - fraction);

  Vector2D left_top = left_bottom + (orthogonal * -height);
  Vector2D right_top = right_bottom + (orthogonal * -height);

  SDL_RenderDrawLine(renderer,
                     left_bottom.getX(),
                     left_bottom.getY(),
                     right_top.getX(),
                     right_top.getY());
  SDL_RenderDrawLine(renderer,
                     right_bottom.getX(),
                     right_bottom.getY(),
                     left_top.getX(),
                     left_top.getY());
  SDL_RenderDrawLine(renderer,
                     right_bottom.getX(),
                     right_bottom.getY(),
                     right_top.getX(),
                     right_top.getY());
  SDL_RenderDrawLine(renderer,
                     left_bottom.getX(),
                     left_bottom.getY(),
                     left_top.getX(),
                     left_top.getY());
}

void
Flipper::update(f64 delta, const Map& map)
{
  if (!active_)
    return;

  if (progress_ == 0) {
    setMovingDirection(RIGHT);
    setMoveDelay(STAGE_2_MOVING_DELAY_);
  }

  move(delta, map);
}
