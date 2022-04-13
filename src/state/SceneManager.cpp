
#include "SceneManager.hpp"
#include "../utils/Utils.hpp"
#include "GameScene.hpp"
#include "LevelSelectionScene.hpp"

template<typename C, typename T>
bool
contains(C&& c, T e)
{
  return std::find(std::begin(c), std::end(c), e) != std::end(c);
}

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

std::unique_ptr<Scene>
get_corresponding_scene(State state)
{
  switch (state) {
    case STATE_TITLE_SCREEN: {
      return std::make_unique<TitleScreen>();
      break;
    }
    case STATE_LEVEL_SELECT: {
      // return std::make_unique<LevelSelectionScene>();
      throw utils::not_implemented();
      break;
    }
    case STATE_GAME_SCENE: {
      return std::make_unique<GameScene>(0);
      break;
    }
    case STATE_PAUSE_MENU: {
      throw utils::not_implemented();
      break;
    }
    case STATE_WIN_SCREEN: {
      throw utils::not_implemented();
      break;
    }
    case STATE_DEATH_SCREEN: {
      throw utils::not_implemented();
      break;
    }

    default:
      throw utils::not_implemented();
      break;
  }
}

void
SceneManager::switch_scene()
{
  if (current_state_ != next_state_) {
    current_scene_p_.reset();
    current_scene_p_ = get_corresponding_scene(next_state_);
    current_state_ = next_state_;
  }
}

void
SceneManager::set_next_state(State next_requested_state)
{
  switch (current_state_) {
    case STATE_GAME_SCENE: {
      std::vector<State> valid_states{ STATE_TITLE_SCREEN };
      if (!contains(valid_states, next_requested_state)) {
        throw utils::non_valid_state_switch();
        return;
      }
      break;
    }
    case STATE_TITLE_SCREEN: {
      std::vector<State> valid_states{ STATE_GAME_SCENE };
      if (!contains(valid_states, next_requested_state)) {
        throw utils::non_valid_state_switch();
        return;
      }
      break;
    }
    case STATE_LEVEL_SELECT: {
      std::vector<State> valid_states{ STATE_GAME_SCENE };
      if (!contains(valid_states, next_requested_state)) {
        throw utils::non_valid_state_switch();
        return;
      }
      break;
    }
    case STATE_WIN_SCREEN: {
      std::vector<State> valid_states{ STATE_LEVEL_SELECT };
      if (!contains(valid_states, next_requested_state)) {
        throw utils::non_valid_state_switch();
        return;
      }
      break;
    }
    case STATE_DEATH_SCREEN: {
      std::vector<State> valid_states{ STATE_LEVEL_SELECT, STATE_GAME_SCENE };
      if (!contains(valid_states, next_requested_state)) {
        throw utils::non_valid_state_switch();
        return;
      }
      break;
    }
    default:
      throw utils::non_valid_state_switch();
      return;
      break;
  }
  next_state_ = next_requested_state;
}
