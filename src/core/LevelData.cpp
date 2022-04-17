//
// Created by massimo on 13/04/2022.
//

#include "LevelData.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
LevelData::LevelData(u8 level)
  : level_num_{ level }
{
  load(level);
}

bool
LevelData::load(u8 level)
{
  std::string file_path =
    LEVELS_DATA_DIR_ + LEVEL_PREFIX_ + std::to_string(level);
  std::ifstream file{ file_path, std::ios::in };

  std::cout << "[Debug]: Trying to open file : " << file_path << std::endl;
  if (!file.is_open()) {
    std::cout << "[Debug]: File not opened" << std::endl;
    return false;
  }
  std::cout << "[Debug]: File opened" << std::endl;

  level_num_ = level;

  std::string line_s;

  // is_continuous
  std::getline(file, line_s);
  is_continuous_ = line_s == "1";

  // score
  std::getline(file, line_s);
  score_ = std::stoul(line_s);

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
  return true;
}

void
LevelData::parseCoordinates(const std::string& coordinates,
                            std::vector<Vector2D>& points)
{
  f32 x, y;
  char delimiter;
  points.clear();
  std::stringstream coordinates_ss(coordinates);
  while (coordinates_ss >> x >> delimiter >> y)
    points.emplace_back(x, y);
}

const std::vector<Vector2D>&
LevelData::getExterior() const
{
  return exterior_;
}

bool
LevelData::isContinuous() const
{
  return is_continuous_;
}

u32
LevelData::getScore() const
{
  return score_;
}

i8
LevelData::getLevelNum() const
{
  return level_num_;
}

const Vector2D&
LevelData::getOrigin() const
{
  return origin;
}

f32
LevelData::getFocal() const
{
  return focal_;
}
