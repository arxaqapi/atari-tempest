//
// Created by massimo on 16/03/2022.
//

#include "GameScene.hpp"
#include "SceneManager.hpp"
#include <cassert>

GameScene::GameScene(u8 level)
  : current_level_data_{ level }
  , map_{ current_level_data_.getExterior(),
          current_level_data_.getInterior(),
          current_level_data_.isContinuous() }
  , spawn_manager_{ map_.size() }
{}

bool
GameScene::loadLevel(u8 level)
{
  if (!current_level_data_.load(level))
    return false;

  spawn_manager_.clear();

  player_.clear();

  map_.reset(current_level_data_.getExterior(),
             current_level_data_.getInterior(),
             current_level_data_.isContinuous());

  return true;
}

void
GameScene::processEvent(SDL_Event event, SceneManager& sm)
{
  switch (event.type) {
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_LEFT)
        player_.setMovingDirection(LEFT);
      else if (event.key.keysym.sym == SDLK_RIGHT)
        player_.setMovingDirection(RIGHT);
      else if (event.key.keysym.sym == SDLK_SPACE)
        player_.shoot();
      break;

    case SDL_KEYUP:
      if (event.key.keysym.sym == SDLK_LEFT ||
          event.key.keysym.sym == SDLK_RIGHT)
        player_.setMovingDirection(NONE);
      else if (event.key.keysym.sym == SDLK_SPACE)
        player_.stopShooting();
      break;

    default:
      break;
  }
}

void
GameScene::update(f64 delta, SceneManager& sm)
{
  player_.update(delta, map_);
  map_.select(player_.getBandNum());
  spawn_manager_.update(delta, map_);

  for (auto& enemy : spawn_manager_.getEnnemies()) {
    if (!enemy.isActive())
      continue;

    if (enemy.isColliding(player_)) {
      enemy.deactivate();
      player_.hit();
      std::cout << "[Debug]: Health = " << unsigned(player_.getHealth()) << std::endl;
    }

    if (player_.getHealth() == 0) {
      // player is dead, go to menu
      sm.set_next_state(STATE_TITLE_SCREEN);
    }
    for (auto& bullet : player_.getBullets()) {
      if (bullet.isActive() && enemy.isColliding(bullet)) {
        bullet.deactivate();
        enemy.hit();
        player_.addScore(200);
        std::cout << "[Debug]: Score = " << player_.getScore() << std::endl;
      }
    }
  }

  if (player_.getScore() >= current_level_data_.getScore()) {
    // level won, go to next level
    if (!loadLevel(current_level_data_.getLevelNum() + 1)) {
      // if no more level, go to menu
       sm.set_next_state(STATE_TITLE_SCREEN);
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
