//
// Created by massimo on 16/03/2022.
//

#include "GameScene.hpp"
#include "../ui/Pen.hpp"
#include "SceneManager.hpp"
#include <cassert>

using namespace std::string_literals;

GameScene::GameScene(u8 level)
  : current_figure_{ static_cast<u8>(level % (Data::N_FIGURES_ - 1)) }
  , current_cycle_{ static_cast<u8>(level / (Data::N_FIGURES_ - 1)) }
  , map_{ level_data.getExterior()[current_figure_],
          level_data.getIsContinuous()[current_figure_],
          level_data.getFocal()[current_figure_],
          level_data.getOrigin()[current_figure_] }
  , spawn_manager_{ map_.size(), level }
{
  if (level > 0)
    player_.addScore(getLevelMaxScore((level - 1) / (Data::N_FIGURES_ - 1),
                                      (level - 1) % (Data::N_FIGURES_ - 1)));
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
  spawn_manager_.update(delta, map_, getCurrentLevelNum());

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

  if (player_.getScore() >= getCurrentLevelMaxScore()) {
    if (gameOver()) // if no more level, go to win screen
      sm.set_next_state(STATE_WIN_SCREEN);
    else
      loadNextLevel();
  }
}

void
GameScene::render(SDL_Renderer* renderer) const
{
  // todo : ne pas stocker en dur ici
  std::vector<std::tuple<int, int, int>> map_standard_colors = {
    { 0, 0, 255 }, { 255, 0, 0 }, { 255, 255, 0 }, { 0, 255, 255 }, { 0, 0, 0 }
  };
  std::vector<std::tuple<int, int, int>> map_selected_colors = {
    { 255, 255, 0 }, { 0, 255, 0 }, { 0, 0, 255 }, { 0, 0, 255 }, { 0, 0, 0 }
  };
  std::vector<std::tuple<int, int, int>> blaster_colors = { { 255, 255, 0 },
                                                            { 0, 255, 0 },
                                                            { 0, 0, 255 },
                                                            { 0, 0, 255 },
                                                            { 255, 255, 0 } };
  std::vector<std::tuple<int, int, int>> flipper_colors = { { 255, 0, 0 },
                                                            { 238, 130, 238 },
                                                            { 0, 255, 0 },
                                                            { 0, 255, 0 },
                                                            { 255, 0, 0 } };
  std::vector<std::tuple<int, int, int>> tanker_colors = { { 238, 130, 238 },
                                                           { 127, 0, 255 },
                                                           { 0, 255, 255 },
                                                           { 238, 130, 238 },
                                                           { 238, 130, 238 } };
  std::vector<std::tuple<int, int, int>> spiker_colors = {
    { 0, 255, 0 }, { 0, 255, 255 }, { 255, 0, 0 }, { 255, 0, 0 }, { 0, 255, 0 }
  };

  // Select the color for drawing. It is set to black here.
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  // Clear the entire screen to our selected color.
  SDL_RenderClear(renderer);

  // Render map
  map_.render(renderer,
              map_standard_colors[current_cycle_],
              map_selected_colors[current_cycle_]);

  // Render player
  player_.render(renderer, map_, blaster_colors[current_cycle_]);

  // Render enemies
  spawn_manager_.render(renderer,
                        map_,
                        flipper_colors[current_cycle_],
                        tanker_colors[current_cycle_],
                        spiker_colors[current_cycle_]);

  // Draw text
  Pen::draw_string(
    "Score: "s + std::to_string(player_.getScore()), 0, 26, renderer);
  Pen::draw_string(
    "Health: "s + std::to_string(player_.getHealth()), 0, 56, renderer);
  Pen::draw_string(
    "Level "s + std::to_string(getCurrentLevelNum()), 0, 82, renderer);
}

u32
GameScene::getCurrentLevelMaxScore() const
{
  return getLevelMaxScore(current_cycle_, current_figure_);
}

u8
GameScene::getCurrentLevelNum() const
{
  return current_figure_ + (Data::N_FIGURES_ - 1) * current_cycle_;
}

void
GameScene::loadNextLevel()
{
  current_figure_ = (current_figure_ + 1) % (Data::N_FIGURES_ - 1);

  if (current_figure_ == 0)
    current_cycle_ += 1;

  map_.load(level_data.getExterior()[current_figure_],
            level_data.getIsContinuous()[current_figure_],
            level_data.getFocal()[current_figure_],
            level_data.getOrigin()[current_figure_]);

  spawn_manager_.load(map_.size(), getCurrentLevelNum());

  player_.clear();
}

bool
GameScene::gameOver() const
{
  return current_cycle_ == Data::N_CYCLES_ &&
         current_figure_ == Data::N_FIGURES_ - 1;
}

u32
GameScene::getLevelMaxScore(u8 cycle, u8 figure)
{
  return 1000 + (cycle + 1) * std::pow(figure + 1, 2) * 600 +
         cycle * Data::N_FIGURES_ * Data::N_FIGURES_ * 600;
}
