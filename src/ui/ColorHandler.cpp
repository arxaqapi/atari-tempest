/**
 * @file ColorHandler.cpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
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
  i32 buff;
  i32 r, g, b;

  std::ifstream file{ COLOR_DATA_PATH_, std::ios::in };
  if (!file.is_open())
    throw errors::FileNotOpened();

  // get number of colors
  file >> buff;
  colors_.reserve(buff);

  // Get all n (8) colors
  for (i32 i = 0; i < buff; i++) {
    file >> r >> g >> b;
    colors_.emplace_back(r, g, b);
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
ColorHandler::getMapStandardColor(i32 cycle) const
{
  return colors_[color_indices_[0][cycle]];
}

const color&
ColorHandler::getMapSelectedColor(i32 cycle) const
{
  return colors_[color_indices_[1][cycle]];
}

const color&
ColorHandler::getBlasterColor(i32 cycle) const
{
  return colors_[color_indices_[2][cycle]];
}

const color&
ColorHandler::getFlipperColor(i32 cycle) const
{
  return colors_[color_indices_[3][cycle]];
}

const color&
ColorHandler::getTankerColor(i32 cycle) const
{
  return colors_[color_indices_[4][cycle]];
}

const color&
ColorHandler::getSpikerColor(i32 cycle) const
{
  return colors_[color_indices_[5][cycle]];
}

const color&
ColorHandler::getScoreColor(i32 cycle) const
{
  return colors_[color_indices_[6][cycle]];
}