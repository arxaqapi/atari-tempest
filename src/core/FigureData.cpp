//
// Created by massimo on 13/04/2022.
//

#include "FigureData.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
FigureData::FigureData(u8 level)
  : figure_num_{ level }
{
  load(level);
}

bool
FigureData::load(u8 figure)
{
  std::string file_path =
    FIGURES_DATA_DIR_ + FIGURE_PREFIX_ + std::to_string(figure);
  std::ifstream file{ file_path, std::ios::in };

  std::cout << "[Debug]: Trying to open file : " << file_path << std::endl;
  if (!file.is_open()) {
    std::cout << "[Debug]: File not opened" << std::endl;
    return false;
  }
  std::cout << "[Debug]: File opened" << std::endl;

  figure_num_ = figure;

  std::string line_s;

  // is_continuous
  std::getline(file, line_s);
  is_continuous_ = line_s == "1";

  // focal_
  std::getline(file, line_s);
  focal_ = std::stof(line_s);

  // origin
  std::getline(file, line_s);
  f32 x, y;
  char delimiter;
  std::stringstream coordinates_ss(line_s);
  coordinates_ss >> x >> delimiter >> y;
  origin.set(x, y);

  // exterior coordinates
  std::getline(file, line_s);
  coordinates_ss.clear();
  coordinates_ss.str(line_s);
  exterior_.clear();
  while (coordinates_ss >> x >> delimiter >> y)
    exterior_.emplace_back(x, y);

  file.close();

  std::cout << "file loaded" << std::endl;
  return true;
}

const std::vector<Vector2D>&
FigureData::getExterior() const
{
  return exterior_;
}

bool
FigureData::isContinuous() const
{
  return is_continuous_;
}

i8
FigureData::getFigureNum() const
{
  return figure_num_;
}

const Vector2D&
FigureData::getOrigin() const
{
  return origin;
}

f32
FigureData::getFocal() const
{
  return focal_;
}
