//
// Created by massimo on 16/03/2022.
//

#ifndef TEMPEST_ATARI_GAMESCENE_HPP
#define TEMPEST_ATARI_GAMESCENE_HPP

#include "../core/Blaster.hpp"
#include "../core/Bullet.hpp"
#include "../core/Data.hpp"
#include "../core/FigureData.hpp"
#include "../core/Flipper.hpp"
#include "../core/GameObjectPool.hpp"
#include "../core/Map.hpp"
#include "../core/SpawnManager.hpp"
#include "../utils/Vector2D.hpp"
#include "Scene.hpp"
#include <string>
#include <vector>

class SceneManager;

class GameScene : public Scene
{
private:
  FigureData current_figure_data_;
  u8 current_cycle_ = 0;
  Map map_;
  Blaster player_;
  SpawnManager spawn_manager_;

public:
  GameScene() = delete;
  GameScene(const GameScene& game_scene) = default;
  explicit GameScene(u8 level);

  bool loadFigure(u8 figure);
  bool loadNextLevel();
  bool gameOver() const;
  static u32 getLevelMaxScore(u8 cycle, u8 figure);
  u32 getCurrentLevelMaxScore() const;
  u8 getCurrentLevelNum() const;
  void processEvent(SDL_Event* event, SceneManager& sm) override;
  void update(f64 delta, SceneManager& sm) override;
  void render(SDLW::Renderer& renderer) const override;
};

#endif // TEMPEST_ATARI_GAMESCENE_HPP
