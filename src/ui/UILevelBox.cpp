/**
 * @file UILevelBox.cpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-14
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "UILevelBox.hpp"
#include "iostream"

UILevelBox::UILevelBox(int x, int y, int w, int h)
  : UIElement{ x, y, w, h }
{}

UILevelBox::~UILevelBox() {}

void
UILevelBox::update()
{}

void
UILevelBox::render(SDL_Renderer* r) const
{
  render(r, false);
}

void
UILevelBox::render(SDL_Renderer* r, bool selected) const
{
  if (selected) {
    SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
  } else {
    SDL_SetRenderDrawColor(r, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  }
  SDL_RenderDrawRect(r, &bounding_box_);
  SDL_Rect inside = { bounding_box_.x + 1,
                      bounding_box_.y + 1,
                      bounding_box_.w - 2,
                      bounding_box_.h - 2 };
  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(r, &inside);
}
