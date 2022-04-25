/**
 * @file UILevelCarousel.cpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-17
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "UILevelCarousel.hpp"
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;

UILevelCarousel::UILevelCarousel(int x,
                                 int y,
                                 int w,
                                 int h)
  : UIElement{ x, y, w, h }
{
  for (size_t i = 0; i < Data::N_LEVELS_; ++i) {
    UILevelBox b{ (u32)i, 200 + ((int)i * 130), 390, 120, 120 };
    ui_elements_.push_back(b);
  }
}

UILevelCarousel::~UILevelCarousel() {}

void
UILevelCarousel::update()
{}

void
UILevelCarousel::render(SDL_Renderer* r) const
{
  // Draw UI
  for (size_t i = 0; i < ui_elements_.size(); i++) {
    bool selected = (selected_level_ - offset_) == (int)i;
    ui_elements_[i].render(r, selected);
  }
}

void
UILevelCarousel::go_right()
{
  int max = Data::N_LEVELS_ - 1;
  if ((selected_level_ - offset_) == 4 && max >= 5 && selected_level_ < max) {
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
  sm.set_next_state(STATE_GAME_SCENE, selected_level_);
}

void
UILevelCarousel::cycle_right()
{
  std::cout << "[Debug] - Cycling right, at offset = " << offset_ << std::endl;
  for (auto& e : ui_elements_) {
    e.set_level_n(e.get_level_n() + 1);
  }
  ++offset_;
  ++selected_level_;
}

void
UILevelCarousel::cycle_left()
{
  std::cout << "[Debug] - Cycling left, at offset = " << offset_ << std::endl;
  for (auto& e : ui_elements_) {
    e.set_level_n(e.get_level_n() - 1);
  }
  --offset_;
  --selected_level_;
}
