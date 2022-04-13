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
Bullet::activate(const Map& map, u8 band_num)
{
  GameObject::activate(map, band_num, 0.01, BACKWARD, 0);
  collider_.w = 10;
  collider_.h = 10;
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
  // drawing collider rectangle for now...
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderDrawRect(renderer, &collider_);
}
