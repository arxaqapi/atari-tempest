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

  Vector2D p = map.calcPosition(band_num_, progress_);
  collider_.x = p.getX();
  collider_.y = p.getY();
  collider_.w = 20;
  collider_.h = 20;
}

void
Blaster::render(SDL_Renderer* renderer, const Map& map) const
{
  if (!active_)
    return;
  bullets_.render(renderer, map);
  // drawing collider rectangle for now...
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderDrawRect(renderer, &collider_);
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

std::vector<Bullet>&
Blaster::getBullets()
{
  return bullets_.getPool();
}

void
Blaster::hit()
{
  health_ = std::max(health_ - 1, 0);
}

f32
Blaster::getScore() const
{
  return score_;
}

void
Blaster::addScore(f32 score)
{
  score_+=score;
}

u8
Blaster::getHealth() const
{
  return health_;
}
