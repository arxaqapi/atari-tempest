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

  const Band& band = map.getBand(band_num_);
  auto exterior = band.getExterior();

  f32 x = band.getExterCenter().vec_to(exterior.first).magnitude();

  Vector2D inner_left = band.calcPosition({ x * 0.9f, 0 });
  Vector2D inner_right = band.calcPosition({ -x * 0.9f, 0 });
  Vector2D inner_top = band.calcPosition({ 0, -10 });
  Vector2D outer_top = band.calcPosition({ 0, -25 });
  Vector2D claw_left = band.calcPosition({ x * 0.2f, 20 });
  Vector2D claw_right = band.calcPosition({ -x * 0.2f, 20 });

  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

  SDL_RenderDrawLineF(renderer,
                      exterior.first.getX(),
                      exterior.first.getY(),
                      claw_left.getX(),
                      claw_left.getY());
  SDL_RenderDrawLineF(renderer,
                      exterior.second.getX(),
                      exterior.second.getY(),
                      claw_right.getX(),
                      claw_right.getY());
  SDL_RenderDrawLineF(renderer,
                      exterior.first.getX(),
                      exterior.first.getY(),
                      outer_top.getX(),
                      outer_top.getY());
  SDL_RenderDrawLineF(renderer,
                      exterior.second.getX(),
                      exterior.second.getY(),
                      outer_top.getX(),
                      outer_top.getY());
  SDL_RenderDrawLineF(renderer,
                      inner_left.getX(),
                      inner_left.getY(),
                      inner_top.getX(),
                      inner_top.getY());
  SDL_RenderDrawLineF(renderer,
                      inner_right.getX(),
                      inner_right.getY(),
                      inner_top.getX(),
                      inner_top.getY());
  SDL_RenderDrawLineF(renderer,
                      claw_left.getX(),
                      claw_left.getY(),
                      inner_left.getX(),
                      inner_left.getY());
  SDL_RenderDrawLineF(renderer,
                      claw_right.getX(),
                      claw_right.getY(),
                      inner_right.getX(),
                      inner_right.getY());
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