//
// Created by massimo on 16/03/2022.
//

#include "Data.hpp"
#include "../utils/Errors.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

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

//  for (int i = 0; i < N_FIGURES_; ++i) {
//    for (int j = 0; j < N_BANDS_PER_FIGURE_; ++j) {
//
//    }
//    std::cout << exterior_[i] << " ";
//  }
}

void
Data::readCoords(std::ifstream& file,
                 std::vector<Vector2D>& coords,
                 u8 n_coords)
{
  f32 x, y;
  std::string x_s, y_s;
  std::stringstream x_ss, y_ss;

  std::getline(file, x_s);
  std::cout << "X " << x_s;
  std::getline(file, y_s);
  std::cout << "Y" << y_s;
  x_ss.str(x_s);
  y_ss.str(y_s);
  for (int j = 0; j < n_coords; ++j) {
    x_ss >> x;
    y_ss >> y;
    coords.emplace_back(x, y);
  }
}
