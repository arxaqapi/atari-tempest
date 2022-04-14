#pragma once

#include "GameScene.hpp"
#include "Scene.hpp"
#include "TitleScreen.hpp"
#include <memory>

enum State
{
  STATE_TITLE_SCREEN,
  STATE_LEVEL_SELECT,
  STATE_GAME_SCENE,
  STATE_PAUSE_MENU,
  STATE_WIN_SCREEN,
  STATE_DEATH_SCREEN
};

class SceneManager
{
private:
  std::unique_ptr<Scene> current_scene_p_ = std::make_unique<TitleScreen>();
  State current_state_ = STATE_TITLE_SCREEN; // TODO: to set at right place
  State next_state_ = STATE_TITLE_SCREEN;
  int requested_level_ = 0;

  /**
   * @brief Destroys the current scene object and affects the new requested one
   *
   */
  void switch_scene();
  std::unique_ptr<Scene> get_corresponding_scene(State state);

public:
  SceneManager();
  ~SceneManager();

  /**
   * @brief Set the next state variable to the requested next state
   * and checks if the switch is authorized
   *
   * @param next_requested_state
   */
  void set_next_state(State next_requested_state);

  void set_next_state(State next_requested_state, int level);

  Scene& get_current_scene() { return *current_scene_p_; }

  void update(f64 delta);
};
