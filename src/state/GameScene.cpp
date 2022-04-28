//
// Created by massimo on 16/03/2022.
//

#include "GameScene.hpp"
#include "../ui/Pen.hpp"
#include "SceneManager.hpp"
#include <cassert>

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
GameScene::processEvent(SDL_Event* event, SceneManager&)
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

  handleCollisions(spawn_manager_.getFlippers(), 200);

  handleCollisions(spawn_manager_.getSpikers(), 50);

  auto f = [this](Bullet& bullet, Tanker& tanker) {
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
    sm.set_next_state(STATE_DEATH_SCREEN);

  // player finished the level
  if (player_.getScore() >= getCurrentLevelMaxScore()) {
    if (gameOver()) // if no more level, go to win screen
      sm.set_next_state(STATE_WIN_SCREEN);
    else
      loadNextLevel();
  }
}

void
GameScene::render(SDLW::Renderer& renderer) const
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
  renderer.SetRenderDrawColor(0, 0, 0, 255);

  // Clear the entire screen to our selected color.
  renderer.RenderClear();

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
  Pen::draw_string(std::to_string(player_.getScore()), 20, 46, renderer, 1.7);
  Pen::draw_string(std::to_string(getCurrentLevelNum()),
                   280,
                   32,
                   renderer,
                   color{ 0x00, 0xFF, 0x00 });

  // Render life points
  renderer.SetRenderDrawColor(0xFF, 0, 0, SDL_ALPHA_OPAQUE);
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

template<class GameObjectType>
void
GameScene::handleCollisions(std::vector<GameObjectType>& enemies,
                            u32 associated_score)
{
  auto f = [](Bullet& bullet, GameObjectType& enemy) {return;};
  handleCollisions(enemies, associated_score, f);
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
        on_bullet_collision(bullet, enemy);
      }
    }
  }
}