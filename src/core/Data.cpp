//
// Created by massimo on 16/03/2022.
//

#include "Data.hpp"
#include <cassert>
Data::Data(std::string data_path)
{
  loadData(data_path);
}

const std::vector<Vector2D>&
Data::getExterior(u8 i) const
{
  assert(i < n_levels);
  return exteriors_[i];
}

const std::vector<Vector2D>&
Data::getInterior(u8 i) const
{
  assert(i < n_levels);
  return interiors_[i];
}

bool
Data::isContinuous(u8 i) const
{
  assert(i < n_levels);
  return is_continuous_[i];
}

u8
Data::getNLevels() const
{
  return n_levels;
}

void
Data::loadData(std::string data_path)
{}
