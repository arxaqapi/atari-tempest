
#include "SceneManager.hpp"
#include "../utils/Utils.hpp"
#include "SLevelSelect.hpp"

template<typename C, typename T>
bool
contains(C&& c, T e)
{
  return std::find(std::begin(c), std::end(c), e) != std::end(c);
};

SceneManager::SceneManager(/* args */) {}

SceneManager::~SceneManager() {}

bool
SceneManager::switch_scene(State next_s)
{
  // STATE_TITLE_SCREEN,
  // STATE_LEVEL_SELECT,
  // STATE_LEVEL_1,
  // STATE_LEVEL_2,
  // STATE_LEVEL_3,
  // STATE_LEVEL_4,
  // STATE_PAUSE_MENU,
  // STATE_WIN_SCREEN,
  // STATE_DEATH_SCREEN
  switch (current_state_) {
    case STATE_TITLE_SCREEN: {
      if (next_s != STATE_LEVEL_SELECT) {
        throw utils::non_valid_state_switch();
      } else {
        current_scene_.reset(); // destroy object
        current_scene_ = std::make_unique<SLevelSelect>();
        return true;
      }
      break;
    }
    case STATE_LEVEL_SELECT: {
      std::vector<State> valid_states{
        STATE_LEVEL_1, STATE_LEVEL_2, STATE_LEVEL_3, STATE_LEVEL_4
      };
      if (!contains(valid_states, next_s)) {
        throw utils::non_valid_state_switch();
      } else {
        current_scene_.reset(); // destroy object
        // TODO: select the object to construct based on next state
        // current_scene_ = std::make_unique<SLevel1>();
        throw utils::not_implemented();
        return true;
      }
      break;
    }
    case STATE_DEATH_SCREEN: {
      std::vector<State> valid_states{
        STATE_LEVEL_1, STATE_LEVEL_2, STATE_LEVEL_3, STATE_LEVEL_4
      };
      if (!contains(valid_states, next_s)) {
        throw utils::non_valid_state_switch();
      } else {
        current_scene_.reset(); // destroy object
        // TODO: select the object to construct based on next state
        // current_scene_ = std::make_unique<SLevel1>();
        throw utils::not_implemented();
        return true;
      }
      break;
    }

    default:
      break;
  }
  return false;
}