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
  , spawn_manager_{ map_.size() }
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
{
  switch( event.type ) {
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_LEFT)
        player_.setMovingDirection(LEFT);
      else if (event.key.keysym.sym == SDLK_RIGHT)
        player_.setMovingDirection(RIGHT);
      else if (event.key.keysym.sym == SDLK_SPACE)
        player_.shoot();
      break;

    case SDL_KEYUP:
      if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)
        player_.setMovingDirection(NONE);
      else if (event.key.keysym.sym == SDLK_SPACE)
        player_.stopShooting();
      break;

    default:
      break;
  }
}

void
GameScene::update(f64 delta)
{
  player_.update(delta, map_);
  map_.select(player_.getBandNum());
  spawn_manager_.update(delta, map_);

  for (auto &enemy : spawn_manager_.getEnnemies()) {
    if (!enemy.isActive())
      continue;
    if (enemy.isColliding(player_)) {
      enemy.deactivate();
      // todo: hit player
    }
    std::vector<Bullet> &bullets = player_.getBullets();
    for (auto &bullet : bullets) {
      if (bullet.isActive() && enemy.isColliding(bullet)) {
          bullet.deactivate();
          enemy.deactivate();
          // todo: score ++
      }
    }
  }
}

void
GameScene::render(SDL_Renderer* renderer) const
{
  // Select the color for drawing. It is set to black here.
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  // Clear the entire screen to our selected color.
  SDL_RenderClear(renderer);

  // Render map
  map_.render(renderer);

  // Render player
  player_.render(renderer, map_);

  // Render enemies
  spawn_manager_.render(renderer, map_);
}
