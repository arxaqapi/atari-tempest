//
// Created by massimo on 16/03/2022.
//

#include "GameScene.hpp"
#include "../ui/Pen.hpp"
#include "SceneManager.hpp"
#include <cassert>

using namespace std::string_literals;

GameScene::GameScene(u8 level)
  : GameScene(level, level / 15)
{}

GameScene::GameScene(u8 level, u8 cycle)
  : current_figure_data_{ level  % 15 }
  , current_level_ {level}
  , current_cycle_{ cycle }
  , map_{ current_figure_data_.getExterior(),
          current_figure_data_.isContinuous(),
          current_figure_data_.getFocal(),
          current_figure_data_.getOrigin() }
  , spawn_manager_{ map_.size() }
{}

bool
GameScene::loadFigure(u8 figure)
{
  if (!current_figure_data_.load(figure))
    return false;

  map_.load(current_figure_data_.getExterior(),
            current_figure_data_.isContinuous(),
            current_figure_data_.getFocal(),
            current_figure_data_.getOrigin());

  spawn_manager_.load(map_.size());

  player_.clear();

  return true;
}

void
GameScene::processEvent(SDL_Event* event, SceneManager& sm)
{
  switch (event->type) {
    case SDL_KEYDOWN:
      if (event->key.keysym.sym == SDLK_LEFT)
        player_.setMovingDirection(LEFT);
      else if (event->key.keysym.sym == SDLK_RIGHT)
        player_.setMovingDirection(RIGHT);
      else if (event->key.keysym.sym == SDLK_SPACE)
        player_.shoot();
      break;

    case SDL_KEYUP:
      if (event->key.keysym.sym == SDLK_LEFT ||
          event->key.keysym.sym == SDLK_RIGHT)
        player_.setMovingDirection(NONE);
      else if (event->key.keysym.sym == SDLK_SPACE)
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

  for (auto& flipper : spawn_manager_.getFlippers()) {
    if (!flipper.isActive())
      continue;

    if (flipper.isColliding(player_)) {
      flipper.deactivate();
      player_.hit();
      spawn_manager_.clear();
    }

    // chasing player
    if (flipper.getFrontProgression() == 0 &&
        flipper.getBandNum() < player_.getBandNum())
      flipper.setBandChangeDirection(RIGHT);
    else if (flipper.getFrontProgression() == 0 &&
             flipper.getBandNum() > player_.getBandNum())
      flipper.setBandChangeDirection(LEFT);

    if (player_.getHealth() == 0) {
      // player is dead, go to menu
      sm.set_next_state(STATE_DEATH_SCREEN);
    }

//    handleBulletsCollision(bullets, flippers, score, []);
    for (auto& bullet : player_.getBullets()) {
      if (bullet.isActive() && bullet.isColliding(flipper)) {
        flipper.deactivate();
        bullet.deactivate();
        player_.addScore(200);
      }
    }
  }

  for (auto& tanker : spawn_manager_.getTankers()) {
    if (!tanker.isActive())
      continue;
    for (auto& bullet : player_.getBullets()) {
      if (bullet.isActive() && bullet.isColliding(tanker)) {
        bullet.deactivate();
        tanker.deactivate();
        spawn_manager_.spawnFlipper(map_.getLeftBandNum(tanker.getBandNum()),
                                    tanker.getFrontProgression(),
                                    LEFT);
        spawn_manager_.spawnFlipper(map_.getRightBandNum(tanker.getBandNum()),
                                    tanker.getFrontProgression(),
                                    RIGHT);
        player_.addScore(150);
      }
    }
  }

  for (auto& spiker : spawn_manager_.getSpikers()) {
    if (!spiker.isActive())
      continue;
    for (auto& bullet : player_.getBullets()) {
      if (bullet.isActive() && bullet.isColliding(spiker)) {
        bullet.deactivate();
        spiker.hit();
        player_.addScore(50);
      }
    }
  }

  if (player_.getScore() >= currentLevelMaxScore()) {
    // level won, go to next level
    u8 new_level_num = (current_figure_data_.getFigureNum() + 1) % 15;
    if (new_level_num == 0)
      current_cycle_ += 1;
    ++current_level_;
    if (!loadFigure(new_level_num)) {
      // if no more level, go to win screen
      current_level_ = 0;
      sm.set_next_state(STATE_WIN_SCREEN);
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

  // Draw text
  Pen::draw_string(
    "Score: "s + std::to_string(player_.getScore()), 0, 26, renderer);
  Pen::draw_string(
    "Health: "s + std::to_string(player_.getHealth()), 0, 56, renderer);
  Pen::draw_string(
    "Level "s + std::to_string(current_level_), 0, 78, renderer);
}

f32
GameScene::currentLevelMaxScore() const
{
  return 1000 +
         (current_cycle_ + 1) *
           std::pow(current_figure_data_.getFigureNum() + 1, 2) * 600 +
         current_cycle_ * 16 * 16 * 600;
}
