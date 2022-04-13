//
// Created by massimo on 23/03/2022.
//

#include "Blaster.hpp"

Blaster::Blaster(const Map& map)
  : GameObject(map, 0, true, 0, NONE, MOVE_DELAY_)
{
  collider_.w = 20;
  collider_.h = 20;
}

void
Blaster::update(f64 delta, const Map& map)
{
  if (!active_)
    return;

  bullets_.update(delta, map);

  if (is_shooting_) {
    shoot_delay_.update(delta);
    if (shoot_delay_.complete()) {
      bullets_.create(map, band_num_);
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

u32
Blaster::getScore() const
{
  return score_;
}

void
Blaster::addScore(u32 score)
{
  score_ += score;
}

u8
Blaster::getHealth() const
{
  return health_;
}

void
Blaster::clear()
{
  band_num_ = 0;
  is_shooting_ = false;
  bullets_.clear();
}