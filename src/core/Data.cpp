//
// Created by massimo on 16/03/2022.
//

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

  if (!file.is_open()) {
    // todo : handle error
    return;
  }

  // Is continuous
  for (int i = 0; i < N_FIGURES_; ++i) {
    file >> buf;
    is_continuous_.emplace_back(buf);
  }

  // Focal
  for (int i = 0; i < N_FIGURES_; ++i) {
    file >> buf;
    focal_.emplace_back(buf);
  }

  // Origin
  for (int i = 0; i < N_FIGURES_; ++i) {
    file >> buf;
    origin_[i].setX(buf);
  }
  for (int i = 0; i < N_FIGURES_; ++i) {
    file >> buf;
    origin_[i].setY(buf);
  }

  //   Exterior
  for (int i = 0; i < N_FIGURES_; ++i) {
    for (int j = 0; j < N_BANDS_PER_FIGURE_ && file >> buf; ++j) {
      exterior_[i][j].setX(buf);
    }
  }
  for (int i = 0; i < N_FIGURES_; ++i) {
    for (int j = 0; j < N_BANDS_PER_FIGURE_ && file >> buf; ++j) {
      exterior_[i][j].setY(buf);
    }
  }

  assert(exterior_.size() == N_FIGURES_ && origin_.size() == N_FIGURES_ &&
         focal_.size() == N_FIGURES_ && is_continuous_.size() == N_FIGURES_);
}