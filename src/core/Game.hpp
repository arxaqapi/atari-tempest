/**
 * @file Game.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef H_TEMPEST_GAME_INC_GAMEOBJECT_
#define H_TEMPEST_GAME_INC_GAMEOBJECT_

// #include "../state/Scene.hpp"
#include "../state/SceneManager.hpp"
#include "../state/TitleScreen.hpp"
#include "../utils/types.hpp"
#include "RenderHandler.hpp"
#include <memory>

class Game
{
private:
  bool run_ = true;
  static u16 WINDOWS_WIDTH_;
  static u16 WINDOWS_HEIGHT_;
  SceneManager sm_;
  RenderHandler r_{ WINDOWS_WIDTH_, WINDOWS_HEIGHT_ };
  void stop_() { run_ = false; };

public:
  Game();
  Game(u16 w_width, u16 w_height);
  ~Game();

  void clear();
  void process_events();
  /**
   * @brief Advances game simulation one step and runs the game
   * at a consistent speed despite differences in the underlying hardware
   *
   * @param delta
   */
  void update(f64 delta);
  void render();

  bool is_running() { return run_; };

  static u16 get_width();
};

#endif