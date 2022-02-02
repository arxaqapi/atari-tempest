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

#include "Renderer.hpp"
#include "types.hpp"
class GameObject
{
private:
  Renderer r_;
  bool run_;
  void stop_() { run_ = false; };

public:
  GameObject();
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