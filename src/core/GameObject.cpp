//
// Created by massimo on 23/03/2022.
//

#include "GameObject.hpp"

GameObject::GameObject(u8 band_num, bool active, f32 progress)
  : band_num_{ band_num }
  , active_{ active }
  , progress_{ progress }
{}

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
GameObject::moveLeft(const Map& map)
{
  band_num_ = map.getLeftBandNum(band_num_);
}

void
GameObject::moveRight(const Map& map)
{
  band_num_ = map.getRightBandNum(band_num_);
}

void
GameObject::moveForward()
{
  progress_ = std::max(0.0, progress_ - 0.01); // TODO: améliorer
}

void
GameObject::moveBackward()
{
  progress_ = std::min(1.0, progress_ + 0.01); // TODO: améliorer
}

void
GameObject::activate(u8 band_num, f32 progress)
{
  active_ = true;
  band_num_ = band_num;
  progress_ = progress;
}
