//
// Created by massimo on 23/03/2022.
//

#include "GameObject.hpp"

GameObject::GameObject(f32 progress)
  : progress_{ progress }
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
  progress_ = std::min(0.0, progress_ - 0.005); // TODO: améliorer
}

void
GameObject::moveBackward()
{
  progress_ = std::max(1.0, progress_ + 0.005); // TODO: améliorer
}
