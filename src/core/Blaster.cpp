//
// Created by massimo on 23/03/2022.
//

#include "Blaster.hpp"

void
Blaster::render(SDL_Renderer* renderer, const Map& map) const
{
  Vector2D p = map.calcPosition(band_num_, progress_);
  // draw a rectangle for now...
  SDL_Rect rect;
  rect.x = p.getX();
  rect.y = p.getY();
  rect.w = 20;
  rect.h = 20;
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderDrawRect(renderer, &rect);
}

void
Blaster::update(const Map& map)
{}
