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
  // std::unique_ptr<Scene> current_scene_ =
  // std::make_unique<GameScene>("./data/levels_data.txt");
  std::unique_ptr<Scene> current_scene_ = std::make_unique<TitleScreen>();
  State current_state_ = STATE_TITLE_SCREEN;

public:
  SceneManager();
  ~SceneManager();

  bool switch_scene(State next_s);

  Scene& get_current_scene() { return *current_scene_; }
};
