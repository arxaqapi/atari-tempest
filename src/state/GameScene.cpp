//
// Created by massimo on 16/03/2022.
//

#include "GameScene.hpp"
#include <cassert>

GameScene::GameScene(std::string data_path)
  : levels_data_{ data_path }
  , map_{ levels_data_.getExterior(current_level_),
          levels_data_.getInterior(current_level_),
          levels_data_.isContinuous(current_level_) }
{}

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

void
GameScene::processEvent(SDL_Event event)
{}

void
GameScene::update(f64 delta)
{}

void
GameScene::render(SDL_Renderer* renderer) const
{
  // Select the color for drawing. It is set to black here.
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  // Clear the entire screen to our selected color.
  SDL_RenderClear(renderer);

  // Up until now everything was drawn behind the scenes.
  // This will show the new, red contents of the window.
  SDL_RenderPresent(renderer);

  // Render map
  map_.render(renderer);
}
