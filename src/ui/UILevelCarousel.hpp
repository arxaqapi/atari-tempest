/**
 * @file UILevelCarousel.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-17
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef TEMPEST_ATARI_UILEVELCAROUSEL_HPP
#define TEMPEST_ATARI_UILEVELCAROUSEL_HPP

#include "../state/SceneManager.hpp"
#include "SDL2/SDL.h"
#include "UIElement.hpp"
#include "UILevelBox.hpp"
#include <filesystem>
#include <string>
#include <vector>

class UILevelCarousel : public UIElement
{
private:
  int selected_level_ = 0;
  // std::vector<UILevelBox> available_levels_;
  std::vector<std::filesystem::path> available_levels_;
  std::vector<UILevelBox> ui_elements_;

public:
  UILevelCarousel() = delete;
  UILevelCarousel(int x, int y, int w, int h) = delete;
  UILevelCarousel(std::string levels_dir, int x, int y, int w, int h);
  ~UILevelCarousel();

  void update() override;
  void render(SDL_Renderer* r) const override;
  // void processEvent(SDL_Event* e);

  void go_right();
  void go_left();
  void select(SceneManager& sm);
};

#endif // TEMPEST_ATARI_UILEVELCAROUSEL_HPP