//
// Created by massimo on 16/03/2022.
//

#ifndef TEMPEST_ATARI_GAMESCENE_HPP
#define TEMPEST_ATARI_GAMESCENE_HPP

#include "../core/Blaster.hpp"
#include "../core/Bullet.hpp"
#include "../core/Data.hpp"
#include "../core/Flipper.hpp"
#include "../core/GameObjectPool.hpp"
#include "../core/LevelData.hpp"
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
  LevelData current_level_data_;
  Map map_;
  Blaster player_;
  SpawnManager spawn_manager_;

public:
  GameScene() = delete;
  GameScene(const GameScene& game_scene) = default;
  explicit GameScene(u8 level);

  bool loadLevel(u8 level);

  void processEvent(SDL_Event* event, SceneManager& sm) override;
  void update(f64 delta, SceneManager& sm) override;
  void render(SDL_Renderer* renderer) const override;
};

#endif // TEMPEST_ATARI_GAMESCENE_HPP
