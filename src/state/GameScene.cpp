/**
 * @file GameScene.cpp
 * @author massimo, Tarek Kunze
 * @version 0.1
 * @date 2022-03-16
 *
 * @copyright Copyright (c) 2022
 */

#include "GameScene.hpp"
#include "../ui/Pen.hpp"
#include "SceneManager.hpp"

using namespace std::string_literals;

GameScene::GameScene(u8 level)
  : current_figure_{ static_cast<u8>(level % Data::N_FIGURES_) }
  , current_cycle_{ static_cast<u8>(level / Data::N_FIGURES_) }
  , map_{ level_data.getExterior()[current_figure_],
          level_data.getIsContinuous()[current_figure_],
          level_data.getFocal()[current_figure_],
          level_data.getOrigin()[current_figure_] }
  , spawn_manager_{ map_.size(), level }
{
  if (level > 0)
    player_.addScore(getLevelMaxScore((level - 1) / Data::N_FIGURES_,
                                      (level - 1) % Data::N_FIGURES_));
}

void
GameScene::processEvent(const SDLW::Event& event, SceneManager& sm)
{
  switch (event.getType()) {
    case SDL_KEYDOWN:
      if (event.getKeycode() == SDLK_LEFT)
        player_.setMovingDirection(LEFT);
      else if (event.getKeycode() == SDLK_RIGHT)
        player_.setMovingDirection(RIGHT);
      else if (event.getKeycode() == SDLK_SPACE)
        player_.shoot();
      else if (event.getKeycode() == SDLK_ESCAPE)
        sm.setNextState(STATE_LEVEL_SELECT);
      break;

    case SDL_KEYUP:
      if (event.getKeycode() == SDLK_LEFT || event.getKeycode() == SDLK_RIGHT)
        player_.setMovingDirection(NONE);
      else if (event.getKeycode() == SDLK_SPACE)
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

  handleCollisions(spawn_manager_.getFlippers(), 200);

  handleCollisions(spawn_manager_.getSpikers(), 50);

  auto f = [this](Tanker& tanker) {
    spawn_manager_.spawnFlipper(map_.getLeftBandNum(tanker.getBandNum()),
                                tanker.getFrontProgression(),
                                LEFT);
    spawn_manager_.spawnFlipper(map_.getRightBandNum(tanker.getBandNum()),
                                tanker.getFrontProgression(),
                                RIGHT);
  };
  handleCollisions(spawn_manager_.getTankers(), 150, f);

  // player is dead, go to menu
  if (player_.getHealth() == 0)
    sm.setNextState(STATE_DEATH_SCREEN);

  // player finished the level
  if (player_.getScore() >= getCurrentLevelMaxScore()) {
    if (gameOver()) // if no more level, go to win screen
      sm.setNextState(STATE_WIN_SCREEN);
    else
      loadNextLevel();
  }
}

void
GameScene::render(SDLW::Renderer& renderer) const
{
  // Select the color for drawing. It is set to black here.
  renderer.SetRenderDrawColor(0, 0, 0, 255);

  // Clear the entire screen to our selected color.
  renderer.RenderClear();

  // Render map
  map_.render(renderer,
              color_handler_.getMapStandardColor(current_cycle_),
              color_handler_.getMapSelectedColor(current_cycle_));

  // Render player
  player_.render(
    renderer, map_, color_handler_.getBlasterColor(current_cycle_));

  // Render enemies
  spawn_manager_.render(renderer,
                        map_,
                        color_handler_.getFlipperColor(current_cycle_),
                        color_handler_.getTankerColor(current_cycle_),
                        color_handler_.getSpikerColor(current_cycle_));

  // Draw text
  Pen::drawString(std::to_string(player_.getScore()),
                  20,
                  46,
                  renderer,
                  1.7,
                  color_handler_.getScoreColor(current_cycle_));
  Pen::drawString(std::to_string(getCurrentLevelNum()),
                  280,
                  32,
                  renderer,
                  (current_cycle_ < 4
                     ? color_handler_.getMapStandardColor(current_cycle_)
                     : color{ 0, 0, 255 }));

  // Render life points
  auto health_color = color_handler_.getBlasterColor(current_cycle_);
  renderer.SetRenderDrawColor(std::get<0>(health_color),
                              std::get<1>(health_color),
                              std::get<2>(health_color),
                              SDL_ALPHA_OPAQUE);
  u8 ymid = 80;

  for (u8 i = 0; i < player_.getHealth(); ++i) {
    u8 xmid = 20 + 32 * i;
    renderer.RenderDrawLine(xmid, ymid - 8, xmid - 14, ymid); // TopL band
    renderer.RenderDrawLine(xmid, ymid - 4, xmid - 10, ymid); // TopL- band

    renderer.RenderDrawLine(xmid, ymid - 8, xmid + 14, ymid); // TopR
    renderer.RenderDrawLine(xmid, ymid - 4, xmid + 10, ymid); // TopR-

    renderer.RenderDrawLine(xmid - 2, ymid + 4, xmid - 14, ymid); // BotL band
    renderer.RenderDrawLine(xmid - 2, ymid + 4, xmid - 10, ymid); // BotL- band

    renderer.RenderDrawLine(xmid + 2, ymid + 4, xmid + 14, ymid); // BotR band
    renderer.RenderDrawLine(xmid + 2, ymid + 4, xmid + 10, ymid); // BotR- band
  }
}

void
GameScene::loadNextLevel()
{
  current_figure_ = (current_figure_ + 1) % Data::N_FIGURES_;

  if (current_figure_ == 0)
    current_cycle_ += 1;

  map_.load(level_data.getExterior()[current_figure_],
            level_data.getIsContinuous()[current_figure_],
            level_data.getFocal()[current_figure_],
            level_data.getOrigin()[current_figure_]);

  spawn_manager_.load(map_.size(), getCurrentLevelNum());

  player_.clear();
}

template<class GameObjectType, typename Func>
void
GameScene::handleCollisions(std::vector<GameObjectType>& enemies,
                            u32 associated_score,
                            Func& on_bullet_collision)
{
  for (auto& enemy : enemies) {
    if (!enemy.isActive())
      continue;

    if (enemy.isColliding(player_)) {
      enemy.deactivate();
      player_.hit();
      spawn_manager_.clear();
    }

    for (auto& bullet : player_.getBullets()) {
      if (bullet.isActive() && bullet.isColliding(enemy)) {
        bullet.deactivate();
        enemy.hit();
        player_.addScore(associated_score);
        on_bullet_collision(enemy);
      }
    }
  }
}