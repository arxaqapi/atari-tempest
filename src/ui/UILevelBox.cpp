/**
 * @file UILevelBox.cpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-14
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "UILevelBox.hpp"
#include "../sdlw/SDLW.hpp"
#include "../ui/Pen.hpp"
#include "iostream"

UILevelBox::UILevelBox(u32 level, i32 x, i32 y, i32 w, i32 h)
  : UIElement{ x, y, w, h }
  , level_n_{ level }
{}

UILevelBox::~UILevelBox() {}

void
UILevelBox::update()
{}

void
UILevelBox::render(SDLW::Renderer& renderer) const
{
  render(renderer, false);
}

void
UILevelBox::render(SDLW::Renderer& renderer, bool selected) const
{
  if (selected) {
    // Draw white border
    renderer.SetRenderDrawColor(0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);

    renderer.RenderDrawRect(bounding_box_);
  }

  // Draw Text
  Pen::drawString(std::to_string(level_n_),
                  bounding_box_.x() + bounding_box_.w() / 2 - 10,
                  bounding_box_.y() + 30,
                  renderer,
                  color{ 0x00, 0xFF, 0x00 });
}

void
UILevelBox::set_level_n(u32 new_level)
{
  level_n_ = new_level;
}

u32
UILevelBox::get_level_n()
{
  return level_n_;
}
