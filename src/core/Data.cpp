//
// Created by massimo on 16/03/2022.
//

#include "Data.hpp"
#include "../utils/Errors.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

Data::Data(std::string data_path)
{
  loadData(data_path);
  n_levels_ = exteriors_.size();
}

const std::vector<Vector2D>&
Data::getExterior(u8 i) const
{
  assert(i < n_levels_);
  return exteriors_[i];
}

const std::vector<Vector2D>&
Data::getInterior(u8 i) const
{
  assert(i < n_levels_);
  return interiors_[i];
}

bool
Data::isContinuous(u8 i) const
{
  assert(i < n_levels_);
  return is_continuous_[i];
}

u8
Data::getNLevels() const
{
  return n_levels_;
}

void
Data::parseCoordinates(const std::string& coordinates,
                       std::vector<Vector2D>& points)
{
  f32 x, y;
  char delimiter;
  points.clear();
  std::stringstream coordinates_ss(coordinates);
  while (coordinates_ss >> x >> delimiter >> y)
    points.emplace_back(x, y);
}

void
Data::parseLine(const std::string& line)
{
  std::stringstream line_input{ line };
  std::string is_continuous_s, score_s, exterior_s, interior_s;

  assert(std::getline(line_input, is_continuous_s, ';') &&
         std::getline(line_input, score_s, ';') &&
         std::getline(line_input, exterior_s, ';') &&
         std::getline(line_input, interior_s, ';'));

  assert(is_continuous_s == "0" || is_continuous_s == "1");
  is_continuous_.emplace_back(is_continuous_s == "1");

  scores_.emplace_back(std::stoul(score_s));

  std::vector<Vector2D> exterior, interior;
  parseCoordinates(exterior_s, exterior);
  parseCoordinates(interior_s, interior);
  assert(interior.size() == exterior.size());
  exteriors_.emplace_back(exterior);
  interiors_.emplace_back(interior);
}

void
Data::loadData(const std::string& data_path)
{
  std::ifstream file{ data_path, std::ios::in };

  if (!file.is_open()) {
    throw errors::file_not_opened();
  }

  std::string line_s;

  // header
  std::getline(file, line_s);

  // data
  while (std::getline(file, line_s)) {
    parseLine(line_s);
  }

  file.close();
}

u32
Data::getScore(u8 i) const
{
  assert(i < n_levels_);
  return scores_[i];
}
