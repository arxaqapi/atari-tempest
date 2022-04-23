//
// Created by massimo on 24/03/2022.
//

#include "Bullet.hpp"
#include "../utils/Utils.hpp"
#include <iostream>

Bullet::Bullet()
{
  deactivate();
}

void
Bullet::update(f64 delta, const Map& map)
{
  if (!active_)
    return;

  if ((moving_direction_ == BACKWARD && front_progression_ == 1) ||
      (moving_direction_ == FORWARD && front_progression_ == 0))
    active_ = false;

  move(delta, map);
}

void
Bullet::render(SDL_Renderer* renderer, const Map& map) const
{
  if (!active_)
    return;

  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

  // Draw rect for now...
  f32 fraction =
    utils::easeOutQuad(front_progression_, 1 - map.getFocal()) - map.getFocal();

  const Band& band = map.getBand(band_num_);

  f32 size = 10 * (1 - fraction);

  Vector2D orthogonal = band.getUnitVector().orthogonalVector();
  Vector2D position = band.getExterCenter().vec_to(map.getOrigin()) * fraction;
  Vector2D left = band.getExterCenter() + (orthogonal * (size/2)) + position;
  Vector2D right = band.getExterCenter() + (orthogonal * (-size/2))+ position;
  Vector2D top = band.getExterCenter() + (band.getUnitVector() * (size/2)) + position;
  Vector2D bottom = band.getExterCenter() + (band.getUnitVector() * (-size/2)) + position;

  SDL_RenderDrawLineF(renderer,
                      left.getX(),
                      left.getY(),
                      top.getX(),
                      top.getY());
  SDL_RenderDrawLineF(renderer,
                      top.getX(),
                      top.getY(),
                      right.getX(),
                      right.getY());
  SDL_RenderDrawLineF(renderer,
                      right.getX(),
                      right.getY(),
                      bottom.getX(),
                      bottom.getY());
  SDL_RenderDrawLineF(renderer,
                      bottom.getX(),
                      bottom.getY(),
                      left.getX(),
                      left.getY());
//  SDL_FRect rect{ position.getX(), position.getY(), size, size };
//  SDL_RenderFillRectF(renderer, &rect);
}
