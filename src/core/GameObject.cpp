//
// Created by massimo on 23/03/2022.
//

#include "GameObject.hpp"
#include <iostream>

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
  switch (moving_direction_) {
    case LEFT:
      lateral_progression_ =
        std::max(0.0, lateral_progression_ - delta * lateral_velocity_);
      if (lateral_progression_ == 0 &&
          map.getLeftBandNum(band_num_) != band_num_) {
        band_num_ = map.getLeftBandNum(band_num_);
        lateral_progression_ = 1;
      }
      break;
    case RIGHT:
      lateral_progression_ =
        std::min(1.0, lateral_progression_ + delta * lateral_velocity_);
      if (lateral_progression_ == 1 &&
          map.getRightBandNum(band_num_) != band_num_) {
        band_num_ = map.getRightBandNum(band_num_);
        lateral_progression_ = 0;
      }
      break;
    case FORWARD:
      front_progression_ =
        std::max(0.0, front_progression_ - delta * front_velocity_);
      break;
    case BACKWARD:
      front_progression_ =
        std::min(1.0, front_progression_ + delta * front_velocity_);
      break;
    default:
      break;
  }
}

void
GameObject::activate(u8 band_num,
                     f32 front_progression,
                     f32 lateral_progression,
                     f32 front_velocity,
                     f32 lateral_velocity,
                     e_direction moving_direction)
{
  active_ = true;
  band_num_ = band_num;
  front_progression_ = front_progression;
  lateral_progression_ = lateral_progression;
  front_velocity_ = front_velocity;
  lateral_velocity_ = lateral_velocity;
  moving_direction_ = moving_direction;
}

void
GameObject::deactivate()
{
  active_ = false;
}

bool
GameObject::isColliding(const GameObject& go) const
{
  // todo: améliorer la gestion des collisions
  return band_num_ == go.band_num_ &&
         std::abs(go.front_progression_ - front_progression_) <
           30 * (front_velocity_ + go.front_velocity_);
}

void
GameObject::hit()
{
  deactivate();
}
