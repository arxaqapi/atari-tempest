//
// Created by massimo on 24/03/2022.
//

#include "Bullet.hpp"
#include <iostream>

Bullet::Bullet()
  : Bullet(0)
{}

Bullet::Bullet(u8 band_num)
  : GameObject(band_num, false, 0, BACKWARD, 0)
{}

void
Bullet::activate(u8 band_num)
{
  GameObject::activate(band_num, 0, BACKWARD, 0);
}

void
Bullet::update(f64 delta, const Map& map)
{
  if (!active_)
    return;

  if (progress_ == 1)
    active_ = false;

  move(delta, map);
}

void
Bullet::render(SDL_Renderer* renderer, const Map& map) const
{
  if (!active_)
    return;

  Vector2D p = map.calcPosition(band_num_, progress_);
  // draw a rectangle for now...
  SDL_Rect rect;
  rect.x = p.getX();
  rect.y = p.getY();
  rect.w = 10;
  rect.h = 10;
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderDrawRect(renderer, &rect);
}
