/**
 * @file Map.cpp
 * @author massimo
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */
#include "Map.hpp"
#include "assert.h"

Map::Map(const std::vector<Vector2D>& exterior,
         const std::vector<Vector2D>& interior,
         bool is_continuous)
  : is_continuous_{ is_continuous }
{
  assert(exterior.size() == interior.size());
  assert(exterior.size() > 0);
  for (int i = 0; i < exterior.size() - 1; ++i)
    bands_.emplace_back(
      exterior[i], exterior[i + 1], interior[i], interior[i + 1]);
  bands_[0].select();
}

const Band&
Map::getBand(u8 num_band) const
{
  assert(num_band < bands_.size());
  return bands_[num_band];
}

const Band&
Map::getLeftBand(u8 num_band) const
{
  int left_band_num = selected_band_num_ - 1;
  if (is_continuous_)
    left_band_num %= bands_.size();
  else
    left_band_num = std::min(left_band_num, 0);
  return bands_[left_band_num];
}

const Band&
Map::getRightBand(u8 num_band) const
{
  int right_band_num = selected_band_num_ + 1;
  if (is_continuous_)
    right_band_num %= bands_.size();
  else
    right_band_num =
      std::max(right_band_num, static_cast<int>(bands_.size() - 1));
  return bands_[right_band_num];
}

Vector2D
Map::calcPosition(u8 num_band, f32 depth) const
{
  assert(num_band < bands_.size());
  return bands_[num_band].calcPosition(depth);
}

void
Map::select(u8 num_band)
{
  assert(num_band < bands_.size());
  bands_[selected_band_num_].unselect();
  bands_[num_band].select();
  selected_band_num_ = num_band;
}

void
Map::render(SDL_Renderer* renderer) const
{
  for (auto band : bands_)
    band.render(renderer);
  bands_[selected_band_num_].render(renderer);
}
