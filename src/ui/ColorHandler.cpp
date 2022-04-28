/**
 * @file ColorHandler.cpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "ColorHandler.hpp"
#include "../utils/Errors.hpp"
#include <cassert>
#include <fstream>
#include <iostream>

ColorHandler::ColorHandler()
{
  i32 n_colors;
  i32 buff;
  i32 r, g, b;

  std::ifstream file{ COLOR_DATA_PATH_, std::ios::in };
  if (!file.is_open())
    throw errors::file_not_opened();

  // get number of colors
  file >> n_colors;
  colors_.reserve(n_colors);
  std::cout << "[Color Handling] - n° colors: " << n_colors << std::endl;

  // Get all n (8) colors
  for (i32 i = 0; i < n_colors; i++) {
    file >> r >> g >> b;
    colors_.emplace_back(r, g, b);
    std::cout << "[Color Handling] - Loaded col: " << r << " " << g << " " << b
              << std::endl;
  }

  // get all indices
  for (size_t i = 0; i < color_indices_.size(); i++) {
    for (size_t j = 0; j < color_indices_[0].size(); j++) {
      file >> buff;
      color_indices_[i][j] = buff;
    }
  }
  file.close();
}

ColorHandler::~ColorHandler() {}

const color&
ColorHandler::get_map_standard_colors(i32 cycle) const
{
  return colors_[color_indices_[0][cycle]];
}

const color&
ColorHandler::get_map_selected_colors(i32 cycle) const
{
  return colors_[color_indices_[1][cycle]];
}

const color&
ColorHandler::get_blaster_colors(i32 cycle) const
{
  return colors_[color_indices_[2][cycle]];
}

const color&
ColorHandler::get_flipper_colors(i32 cycle) const
{
  return colors_[color_indices_[3][cycle]];
}

const color&
ColorHandler::get_tanker_colors(i32 cycle) const
{
  return colors_[color_indices_[4][cycle]];
}

const color&
ColorHandler::get_spiker_colors(i32 cycle) const
{
  return colors_[color_indices_[5][cycle]];
}

const color&
ColorHandler::get_score_colors(i32 cycle) const
{
  return colors_[color_indices_[6][cycle]];
}