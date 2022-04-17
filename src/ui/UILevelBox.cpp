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
#include "../sdlw/SDLW.hpp"
#include "../ui/Pen.hpp"
#include "iostream"

UILevelBox::UILevelBox(u32 level, int x, int y, int w, int h)
  : UIElement{ x, y, w, h }
  , level_n_{ level }
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
    // Draw white border
    SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);

    SDL_RenderDrawRect(r, &bounding_box_);
  } else {

    SDL_SetRenderDrawColor(r, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);
    SDLW::RenderFillRect(r,
                         SDLW::Rect(bounding_box_.x + 2,
                                    bounding_box_.y + 2,
                                    bounding_box_.w - 4,
                                    bounding_box_.h - 4));
  }

  // Draw Text
  Pen::draw_string(std::to_string(level_n_),
                   bounding_box_.x + bounding_box_.w / 2 - 10,
                   bounding_box_.y + 30,
                   r);

  // SDL_RenderDrawRect(r, &bounding_box_);
  // SDL_Rect inside = { bounding_box_.x + 1,
  //                     bounding_box_.y + 1,
  //                     bounding_box_.w - 2,
  //                     bounding_box_.h - 2 };
  // SDL_SetRenderDrawColor(r, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);
  // SDL_RenderFillRect(r, &inside);
}
