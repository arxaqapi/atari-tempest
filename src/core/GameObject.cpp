//
// Created by massimo on 23/03/2022.
//

#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject(u8 band_num,
                       bool active,
                       f32 progress,
                       e_direction moving_direction,
                       f64 move_delay)
  : band_num_{ band_num }
  , active_{ active }
  , progress_{ progress }
  , moving_direction_{ moving_direction }
  , move_delay_{ move_delay }
{}

GameObject::GameObject(const Map& map,
                       u8 band_num,
                       bool active,
                       f32 progress,
                       e_direction moving_direction,
                       f64 move_delay)
  : position_{ map.calcPosition(band_num, progress) }
  , band_num_{ band_num }
  , active_{ active }
  , progress_{ progress }
  , moving_direction_{ moving_direction }
  , move_delay_{ move_delay }
  , collider_{ static_cast<int>(position_.getX()),
               static_cast<int>(position_.getY()),
               20,
               20 }
{
  std::cout << collider_.w << std::endl;
}

bool
GameObject::isActive() const
{
  return active_;
}

u8
GameObject::getBandNum() const
{
  return band_num_;
}

void
GameObject::setMovingDirection(e_direction moving_direction)
{
  moving_direction_ = moving_direction;
}

void
GameObject::move(f64 delta, const Map& map)
{
  move_delay_.update(delta);

  if (!move_delay_.complete())
    return;

  switch (moving_direction_) {
    case LEFT:
      band_num_ = map.getLeftBandNum(band_num_);
      break;
    case RIGHT:
      band_num_ = map.getRightBandNum(band_num_);
      break;
    case FORWARD:
      progress_ = std::max(
        0.0, progress_ - delta * 0.0005); // TODO: améliorer (vitesse variable)
      break;
    case BACKWARD:
      progress_ = std::min(
        1.0, progress_ + delta * 0.0005); // TODO: améliorer (vitesse variable)
      break;
    default:
      break;
  }

  move_delay_.reset();

  position_ = map.calcPosition(band_num_, progress_);
  collider_.x = position_.getX();
  collider_.y = position_.getY();
}

void
GameObject::activate(const Map& map,
                     u8 band_num,
                     f32 progress,
                     e_direction moving_direction,
                     f64 move_delay)
{
  active_ = true;
  band_num_ = band_num;
  progress_ = progress;
  moving_direction_ = moving_direction;
  move_delay_.set(move_delay);
  move_delay_.reset();
  position_ = map.calcPosition(band_num, progress);
  collider_.x = position_.getX();
  collider_.y = position_.getY();
}

void
GameObject::setMoveDelay(f64 move_delay)
{
  move_delay_.set(move_delay);
}

void
GameObject::deactivate()
{
  active_ = false;
}

bool
GameObject::isColliding(const GameObject& go) const
{
  return SDL_HasIntersection(&go.collider_, &collider_);
}

void
GameObject::hit()
{
  deactivate();
}
