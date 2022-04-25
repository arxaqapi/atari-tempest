/**
 * @file UILevelBox.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-14
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef TEMPEST_ATARI_UILEVELBOX_HPP
#define TEMPEST_ATARI_UILEVELBOX_HPP

#include "../utils/types.hpp"
#include "UIElement.hpp"

class UILevelBox : public UIElement
{
private:
  u32 level_n_;

public:
  UILevelBox(i32 x, i32 y, i32 w, i32 h) = delete;
  UILevelBox(u32 level, i32 x, i32 y, i32 w, i32 h);
  ~UILevelBox();

  void update() override;
  void render(SDLW::Renderer& renderer) const override;
  void render(SDLW::Renderer& renderer, bool selected) const;

  void set_level_n(u32 new_level);
  u32 get_level_n();
};

#endif // TEMPEST_ATARI_UILEVELBOX_HPP