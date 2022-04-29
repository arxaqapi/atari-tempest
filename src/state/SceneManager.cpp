/**
 * @file SceneManager.cpp
 * @author Tarek Kunze (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */
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
SceneManager::getCorrespondingScene(State state)
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
      throw errors::NotImplemented();
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
      throw errors::NotImplemented();
      break;
  }
}

void
SceneManager::switchScene()
{
  current_scene_p_.reset();
  current_scene_p_ = getCorrespondingScene(next_state_);
  current_state_ = next_state_;
  // resets requested_level_ after usage
  requested_level_ = 0;
}

void
SceneManager::setNextState(State next_requested_state)
{
  switch (current_state_) {
    case STATE_TITLE_SCREEN: {
      std::vector<State> valid_states{ STATE_LEVEL_SELECT };
      if (!contains(valid_states, next_requested_state)) {
        throw errors::NonValidStateSwitch();
        return;
      }
      break;
    }
    case STATE_LEVEL_SELECT: {
      std::vector<State> valid_states{ STATE_GAME_SCENE };
      if (!contains(valid_states, next_requested_state)) {
        throw errors::NonValidStateSwitch();
        return;
      }
      break;
    }
    case STATE_GAME_SCENE: {
      std::vector<State> valid_states{ STATE_TITLE_SCREEN,
                                       STATE_WIN_SCREEN,
                                       STATE_DEATH_SCREEN,
                                       STATE_LEVEL_SELECT };
      if (!contains(valid_states, next_requested_state)) {
        throw errors::NonValidStateSwitch();
        return;
      }
      break;
    }
    case STATE_WIN_SCREEN: {
      std::vector<State> valid_states{ STATE_LEVEL_SELECT };
      if (!contains(valid_states, next_requested_state)) {
        throw errors::NonValidStateSwitch();
        return;
      }
      break;
    }
    case STATE_DEATH_SCREEN: {
      std::vector<State> valid_states{ STATE_LEVEL_SELECT, STATE_GAME_SCENE };
      if (!contains(valid_states, next_requested_state)) {
        throw errors::NonValidStateSwitch();
        return;
      }
      break;
    }
    default:
      throw errors::NonValidStateSwitch();
      return;
      break;
  }
  next_state_ = next_requested_state;
}

void
SceneManager::setNextState(State next_requested_state, i32 level)
{
  requested_level_ = level;
  setNextState(next_requested_state);
}

void
SceneManager::update(f64 delta)
{
  if (current_state_ != next_state_)
    switchScene();
  current_scene_p_->update(delta, *this);
}
