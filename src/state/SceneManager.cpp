
#include "SceneManager.hpp"
#include "../utils/Errors.hpp"
#include "DeathScreen.hpp"
#include "GameScene.hpp"
#include "LevelSelectionScene.hpp"
#include "WinScreen.hpp"

template<typename C, typename T>
bool
contains(C&& c, T e)
{
  return std::find(std::begin(c), std::end(c), e) != std::end(c);
}

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

std::unique_ptr<Scene>
SceneManager::get_corresponding_scene(State state)
{
  switch (state) {
    case STATE_TITLE_SCREEN: {
      return std::make_unique<TitleScreen>();
      break;
    }
    case STATE_LEVEL_SELECT: {
      return std::make_unique<LevelSelectionScene>();
      break;
    }
    case STATE_GAME_SCENE: {
      return std::make_unique<GameScene>(requested_level_);
      break;
    }
    case STATE_PAUSE_MENU: {
      throw errors::not_implemented();
      break;
    }
    case STATE_WIN_SCREEN: {
      return std::make_unique<WinScreen>();
      break;
    }
    case STATE_DEATH_SCREEN: {
      return std::make_unique<DeathScreen>();
      break;
    }

    default:
      throw errors::not_implemented();
      break;
  }
}

void
SceneManager::switch_scene()
{
  current_scene_p_.reset();
  current_scene_p_ = get_corresponding_scene(next_state_);
  current_state_ = next_state_;
  // resets requested_level_ after usage
  requested_level_ = 0;
}

void
SceneManager::set_next_state(State next_requested_state)
{
  switch (current_state_) {
    case STATE_TITLE_SCREEN: {
      std::vector<State> valid_states{ STATE_LEVEL_SELECT };
      if (!contains(valid_states, next_requested_state)) {
        throw errors::non_valid_state_switch();
        return;
      }
      break;
    }
    case STATE_LEVEL_SELECT: {
      std::vector<State> valid_states{ STATE_GAME_SCENE };
      if (!contains(valid_states, next_requested_state)) {
        throw errors::non_valid_state_switch();
        return;
      }
      break;
    }
    case STATE_GAME_SCENE: {
      std::vector<State> valid_states{ STATE_TITLE_SCREEN,
                                       STATE_WIN_SCREEN,
                                       STATE_DEATH_SCREEN };
      if (!contains(valid_states, next_requested_state)) {
        throw errors::non_valid_state_switch();
        return;
      }
      break;
    }
    case STATE_WIN_SCREEN: {
      std::vector<State> valid_states{ STATE_LEVEL_SELECT };
      if (!contains(valid_states, next_requested_state)) {
        throw errors::non_valid_state_switch();
        return;
      }
      break;
    }
    case STATE_DEATH_SCREEN: {
      std::vector<State> valid_states{ STATE_LEVEL_SELECT, STATE_GAME_SCENE };
      if (!contains(valid_states, next_requested_state)) {
        throw errors::non_valid_state_switch();
        return;
      }
      break;
    }
    default:
      throw errors::non_valid_state_switch();
      return;
      break;
  }
  next_state_ = next_requested_state;
}

void
SceneManager::set_next_state(State next_requested_state, int level)
{
  requested_level_ = level;
  set_next_state(next_requested_state);
}

void
SceneManager::update(f64 delta)
{
  if (current_state_ != next_state_)
    switch_scene();
  current_scene_p_->update(delta, *this);
}
