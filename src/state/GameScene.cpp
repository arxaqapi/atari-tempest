//
// Created by massimo on 16/03/2022.
//

#include "GameScene.hpp"
#include <cassert>
void
GameScene::loadLevel(u8 level)
{
  map_.reset(levels_data_.getExterior(level),
             levels_data_.getInterior(level),
             levels_data_.isContinuous(level));
  current_level_ = level;
}

void
GameScene::loadNextLevel()
{
  assert(current_level_ != levels_data_.getNLevels() - 1);
  current_level_++;
  map_.reset(levels_data_.getExterior(current_level_),
             levels_data_.getInterior(current_level_),
             levels_data_.isContinuous(current_level_));
}
