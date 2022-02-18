/**
 * @file GameObject.hpp
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
#include "Renderer.hpp"
#include <memory>

class GameObject
{
private:
  bool run_;
  u16 WINDOWS_WIDTH_ = 960;
  u16 WINDOWS_HEIGHT_ = 540;
  SceneManager sm_;
  Renderer r_{ WINDOWS_WIDTH_, WINDOWS_HEIGHT_ };
  void stop_() { run_ = false; };

public:
  GameObject();
  GameObject(u16 w_width, u16 w_height)
    : WINDOWS_WIDTH_{ w_width }
    , WINDOWS_HEIGHT_{ w_height } {};
  ~GameObject();

  void init();
  void clear();
  void process_events();
  /**
   * @brief Advances game simulation one step and runs the game
   * at a consistent speed despite differences in the underlying hardware
   *
   * @param delta
   */
  void update_state(f64 delta);
  void render();

  bool is_running() { return run_; };
};

#endif