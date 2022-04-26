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
      bullets_.create(band_num_, 0, 0.5, 0.001, 0, BACKWARD);
      shoot_delay_.reset();
    }
  }

  move(delta, map);
}

void
Blaster::render(SDLW::Renderer& renderer,
                const Map& map,
                const color& render_color) const
{
  if (!active_)
    return;
  bullets_.render(renderer, map, render_color);

  const Band& band = map.getBand(band_num_);
  auto exterior = band.getExterior();

  Vector2D exterior_vec =
    exterior.first.vec_to(exterior.second);
                            Vector2D unit_vector = exterior_vec.orthogonalVector().unit();
  Vector2D inner_left = exterior.first.weightedMidPointTo(exterior.second, 0.1);
  Vector2D inner_right =
    exterior.first.weightedMidPointTo(exterior.second, 0.9);

  auto height = exterior_vec.magnitude() * 0.3;
  auto weight = lateral_progression_;
  if (lateral_progression_ > .90)
    weight = .90;
  else if (lateral_progression_ < .1)
    weight = .1;

  Vector2D inner_top =
    exterior.first.weightedMidPointTo(exterior.second, weight) +
    (unit_vector * (-height/2));
  Vector2D outer_top =
    exterior.first.weightedMidPointTo(exterior.second, weight) +
    (unit_vector * -height);

  Vector2D claw_left =
    exterior.first.weightedMidPointTo(exterior.second, .4) + (unit_vector * (height/2));
  Vector2D claw_right =
    exterior.first.weightedMidPointTo(exterior.second, .6) + (unit_vector * (height/2));

  renderer.SetRenderDrawColor(std::get<0>(render_color),
                              std::get<1>(render_color),
                              std::get<2>(render_color),
                              255);

  renderer.RenderDrawLineF(exterior.first.getX(),
                           exterior.first.getY(),
                           claw_left.getX(),
                           claw_left.getY());
  renderer.RenderDrawLineF(exterior.second.getX(),
                           exterior.second.getY(),
                           claw_right.getX(),
                           claw_right.getY());
  renderer.RenderDrawLineF(exterior.first.getX(),
                           exterior.first.getY(),
                           outer_top.getX(),
                           outer_top.getY());
  renderer.RenderDrawLineF(exterior.second.getX(),
                           exterior.second.getY(),
                           outer_top.getX(),
                           outer_top.getY());
  renderer.RenderDrawLineF(
    inner_left.getX(), inner_left.getY(), inner_top.getX(), inner_top.getY());
  renderer.RenderDrawLineF(
    inner_right.getX(), inner_right.getY(), inner_top.getX(), inner_top.getY());
  renderer.RenderDrawLineF(
    claw_left.getX(), claw_left.getY(), inner_left.getX(), inner_left.getY());
  renderer.RenderDrawLineF(claw_right.getX(),
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
  clear();
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
  lateral_progression_ = 0;
  moving_direction_ = NONE;
}