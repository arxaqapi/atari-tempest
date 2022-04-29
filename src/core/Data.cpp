/**
 * @file Data.cpp
 * @author massimo
 * @version 0.1
 * @date 2022-03-16
 *
 * @copyright Copyright (c) 2022
 */

#include "Data.hpp"
#include "../utils/Errors.hpp"
#include <cassert>
#include <fstream>
#include <iostream>

Data::Data()
  : exterior_(N_FIGURES_, std::vector<Vector2D>(N_BANDS_PER_FIGURE_))
  , origin_(N_FIGURES_)
{
  std::ifstream file{ DATA_PATH_, std::ios::in };
  f32 buf;

  if (!file.is_open())
    throw errors::FileNotOpened();

  // Is continuous parsing
  for (u8 i = 0; i < N_FIGURES_; ++i) {
    file >> buf;
    is_continuous_.emplace_back(buf);
  }

  // Focal parsing
  for (u8 i = 0; i < N_FIGURES_; ++i) {
    file >> buf;
    focal_.emplace_back(buf);
  }

  // Origin parsing
  for (u8 i = 0; i < N_FIGURES_; ++i) {
    file >> buf;
    origin_[i].setX(buf);
  }
  for (u8 i = 0; i < N_FIGURES_; ++i) {
    file >> buf;
    origin_[i].setY(buf);
  }

  // Exterior coords parsing
  for (u8 i = 0; i < N_FIGURES_; ++i) {
    for (u8 j = 0; j < N_BANDS_PER_FIGURE_ && file >> buf; ++j) {
      exterior_[i][j].setX(buf);
    }
  }
  for (u8 i = 0; i < N_FIGURES_; ++i) {
    for (u8 j = 0; j < N_BANDS_PER_FIGURE_ && file >> buf; ++j) {
      exterior_[i][j].setY(buf);
    }
  }

  assert(exterior_.size() == N_FIGURES_ && origin_.size() == N_FIGURES_ &&
         focal_.size() == N_FIGURES_ && is_continuous_.size() == N_FIGURES_);
}