//
// Created by massimo on 23/03/2022.
//

#include "Blaster.hpp"

void
Blaster::update(f64 delta, const Map& map)
{
  if (!active_)
    return;

  bullets_.update(delta, map);

  if (is_shooting_) {
    shoot_delay_.update(delta);
    if (shoot_delay_.complete()) {
      bullets_.create(band_num_);
      shoot_delay_.reset();
    }
  }

  move(delta, map);
}

void
Blaster::render(SDL_Renderer* renderer, const Map& map) const
{
  if (!active_)
    return;

  bullets_.render(renderer, map);

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
Blaster::shoot()
{
  is_shooting_ = true;
}

void
Blaster::stopShooting()
{
  is_shooting_ = false;
}
