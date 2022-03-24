//
// Created by massimo on 16/03/2022.
//

#ifndef TEMPEST_ATARI_GAMESCENE_HPP
#define TEMPEST_ATARI_GAMESCENE_HPP

#include "../core/Data.hpp"
#include "../core/Map.hpp"
#include "../utils/Vector2D.hpp"
#include "Scene.hpp"
#include "../core/Blaster.hpp"
#include "../core/Flipper.hpp"
#include <string>
#include <vector>

class GameScene : public Scene
{
private:
  Data levels_data_;
  u8 current_level_{ 0 };
  Map map_;
  Blaster player_;
  Flipper enemy_{2};
  // ...
public:
  GameScene() = default;
  GameScene(const GameScene& game_scene) = default;
  explicit GameScene(std::string data_path);
  void loadLevel(u8 level);
  void loadNextLevel();
  void processEvent(SDL_Event event) override;
  void update(f64 delta) override;
  void render(SDL_Renderer* renderer) const override;
};

#endif // TEMPEST_ATARI_GAMESCENE_HPP
