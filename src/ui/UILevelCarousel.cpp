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

UILevelCarousel::UILevelCarousel(std::string levels_dir,
                                 int x,
                                 int y,
                                 int w,
                                 int h)
  : UIElement{ x, y, w, h }
{
  // recup all levels
  // for each level, create ui element max 5
  std::regex r{ "figure-[0-9]+" };
  // Get all available scenes
  if (fs::exists(levels_dir) && fs::is_directory(levels_dir)) {
    for (const auto& file : fs::directory_iterator(levels_dir)) {
      if (std::regex_match(file.path().filename().string(), r)) {
        available_levels_.push_back(file.path());
      }
    }
  }

  std::sort(available_levels_.begin(),
            available_levels_.end(),
            [](fs::path p1, fs::path p2) {
              return std::stoi(p1.filename().string().substr(6)) <
                     std::stoi(p2.filename().string().substr(6));
            });

  for (size_t i = 0; i < available_levels_.size(); i++) {
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
    bool selected = selected_level_ == (int)i;
    ui_elements_[i].render(r, selected);
  }
}

void
UILevelCarousel::go_right()
{
  selected_level_ = selected_level_ < (int)available_levels_.size() - 1
                      ? selected_level_ + 1
                      : selected_level_;
}

void
UILevelCarousel::go_left()
{
  selected_level_ = selected_level_ > 0 ? selected_level_ - 1 : selected_level_;
}

void
UILevelCarousel::select(SceneManager& sm)
{
  sm.set_next_state(STATE_GAME_SCENE, selected_level_);
}

// void
// UILevelCarousel::processEvent(SDL_Event* e)
// {
//   // if right arrow, selected_level ++
//   // if at end of 5, render with offset
// }