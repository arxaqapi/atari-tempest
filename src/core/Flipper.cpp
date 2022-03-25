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
  Vector2D p = map.calcPosition(band_num_, progress_);
  // draw a rectangle for now...
  SDL_Rect rect;
  rect.x = p.getX();
  rect.y = p.getY();
  rect.w = 20;
  rect.h = 20;
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_RenderDrawRect(renderer, &rect);
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
