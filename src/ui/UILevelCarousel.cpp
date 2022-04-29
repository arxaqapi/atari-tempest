/**
 * @file UILevelCarousel.cpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-17
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "UILevelCarousel.hpp"
#include <algorithm>
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;

inline void
setup_ui_elements(std::vector<UILevelBox>& ui_elements)
{
  for (u8 i = 0; i < UILevelCarousel::AMOUNT_OF_BOXES_; ++i) {
    ui_elements.emplace_back((u32)i, 185 + ((i32)i * 130), 390, 120, 120);
  }
}

UILevelCarousel::UILevelCarousel()
{
  setup_ui_elements(ui_elements_);
}

UILevelCarousel::UILevelCarousel(i32 x, i32 y, i32 w, i32 h)
  : UIElement{ x, y, w, h }
{
  setup_ui_elements(ui_elements_);
}

UILevelCarousel::~UILevelCarousel() {}

void
UILevelCarousel::update()
{}

void
UILevelCarousel::render(SDLW::Renderer& renderer) const
{
  // Draw UI
  for (size_t i = 0; i < ui_elements_.size(); i++) {
    bool selected = (selected_level_ - offset_) == (i32)i;
    ui_elements_[i].render(renderer, selected);
  }
}

void
UILevelCarousel::go_right()
{
  i32 max = Data::N_LEVELS_ - 1;
  if ((selected_level_ - offset_) == AMOUNT_OF_BOXES_ - 1 &&
      max >= AMOUNT_OF_BOXES_ && selected_level_ < max) {
    cycle_right();
  } else if (selected_level_ < max) {
    ++selected_level_;
  }
}

void
UILevelCarousel::go_left()
{
  if ((selected_level_ - offset_) == 0 && selected_level_ > 0) {
    cycle_left();
  } else if (selected_level_ > 0) {
    --selected_level_;
  }
}

void
UILevelCarousel::select(SceneManager& sm)
{
  sm.setNextState(STATE_GAME_SCENE, selected_level_);
}

void
UILevelCarousel::cycle_right()
{
  std::for_each(ui_elements_.begin(), ui_elements_.end(), [](auto& e) {
    e.set_level_n(e.get_level_n() + 1);
  });
  ++offset_;
  ++selected_level_;
}

void
UILevelCarousel::cycle_left()
{
  std::for_each(ui_elements_.begin(), ui_elements_.end(), [](auto& e) {
    e.set_level_n(e.get_level_n() - 1);
  });
  --offset_;
  --selected_level_;
}
