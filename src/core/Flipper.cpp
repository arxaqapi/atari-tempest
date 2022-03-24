//
// Created by massimo on 23/03/2022.
//

#include "Flipper.hpp"

Flipper::Flipper() : GameObject(1)
{}

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
Flipper::update(const Map& map)
{
  if (progress_ == 0)
    moveRight(map);
  else
    moveForward();
}
