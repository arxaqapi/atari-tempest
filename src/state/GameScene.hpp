//
// Created by massimo on 16/03/2022.
//

#ifndef TEMPEST_ATARI_GAMESCENE_HPP
#define TEMPEST_ATARI_GAMESCENE_HPP

#include <vector>
#include <string>
#include "../utils/Vector2D.hpp"
#include "../core/Map.hpp"
#include "../core/Data.hpp"
class GameScene
{
private:
  Data levels_data_;
  u8 current_level_ = 0;
  Map map_;
  // ...
public:
  GameScene() = default;
  GameScene(const GameScene &game_scene) = default;
  explicit GameScene(std::string data_path);
  void loadLevel(u8 level);
  void loadNextLevel();
};

#endif // TEMPEST_ATARI_GAMESCENE_HPP
