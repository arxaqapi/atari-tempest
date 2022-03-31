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
Flipper::activate(u8 band_num)
{
  GameObject::activate(band_num, 1, FORWARD, 0);
}

void
Flipper::render(SDL_Renderer* renderer, const Map& map) const
{
  if (!active_)
    return;
  // drawing collider rectangle for now...
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
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

  Vector2D p = map.calcPosition(band_num_, progress_);
  collider_.x = p.getX();
  collider_.y = p.getY();
  collider_.w = 20;
  collider_.h = 20;
}
