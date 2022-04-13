//
// Created by massimo on 23/03/2022.
//

#include "Flipper.hpp"

Flipper::Flipper()
  : Flipper(0)
{}

Flipper::Flipper(u8 band_num)
  : GameObject(band_num, false, 1, FORWARD, 0)
{}

void
Flipper::activate(const Map& map, u8 band_num)
{
  GameObject::activate(map, band_num, 1, FORWARD, 0);
  collider_.w = 20;
  collider_.h = 20;
}

void
Flipper::render(SDL_Renderer* renderer, const Map& map) const
{
  if (!active_)
    return;
  // drawing collider rectangle for now...
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderDrawRect(renderer, &collider_);
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
