/**
 * @file Map.cpp
 * @author massimo
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 */

#include "Map.hpp"
#include <numeric>

Map::Map(const std::vector<Vector2D>& exterior,
         bool is_continuous,
         f32 focal,
         Vector2D origin)
  : is_continuous_{ is_continuous }
  , focal_{ focal }
  , origin_{ origin }
{
  makeBands(exterior);
}

u8
Map::getLeftBandNum(u8 num_band) const
{
  assert(num_band < bands_.size());
  i32 left_band_num = num_band - 1;
  if (is_continuous_)
    left_band_num %= bands_.size();
  else
    left_band_num = std::max(left_band_num, 0);
  return left_band_num;
}

u8
Map::getRightBandNum(u8 num_band) const
{
  assert(num_band < bands_.size());
  i32 right_band_num = num_band + 1;
  if (is_continuous_)
    right_band_num %= bands_.size();
  else
    right_band_num =
      std::min(right_band_num, static_cast<int>(bands_.size() - 1));
  return right_band_num;
}

void
Map::render(SDLW::Renderer& renderer,
            const color& standard_color,
            const color& accent_color) const
{
  for (auto band : bands_)
    band.render(renderer, standard_color);
  bands_[selected_band_num_].render(renderer, accent_color);
}

void
Map::makeBands(const std::vector<Vector2D>& exterior)
{
  assert(exterior.size() > 0);

  bands_.clear();

  size_t i;
  for (i = 0; i < exterior.size() - 1; ++i)
    bands_.emplace_back(exterior[i], exterior[i + 1], origin_, focal_);
  if (is_continuous_)
    bands_.emplace_back(exterior[i], exterior[0], origin_, focal_);

  avg_band_with_ =
    static_cast<f32>(std::accumulate(
      bands_.begin(),
      bands_.end(),
      0.0,
      [](f32 a, const Band& b) {
        return a +
               b.getExterior().first.vec_to(b.getExterior().second).magnitude();
      })) /
    bands_.size();
}

void
Map::load(const std::vector<Vector2D>& exterior,
          bool is_continuous,
          f32 focal,
          Vector2D origin)
{
  is_continuous_ = is_continuous;
  focal_ = focal;
  origin_ = origin;
  makeBands(exterior);
}
