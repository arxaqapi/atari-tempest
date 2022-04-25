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
#include "UIElement.hpp"
#include "UILevelBox.hpp"
#include <filesystem>
#include <string>
#include <vector>

class UILevelCarousel : public UIElement
{
private:
  i32 selected_level_ = 0;
  std::vector<UILevelBox> ui_elements_;
  u16 offset_ = 0;

public:
  UILevelCarousel() = delete;
  UILevelCarousel(i32 x, i32 y, i32 w, i32 h);
  ~UILevelCarousel();

  void update() override;
  void render(SDLW::Renderer& renderer) const override;

  void go_right();
  void go_left();
  void select(SceneManager& sm);
  void cycle_right();
  void cycle_left();
};

#endif // TEMPEST_ATARI_UILEVELCAROUSEL_HPP