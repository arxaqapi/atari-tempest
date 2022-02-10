/**
 * @file TitleScreen.cpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-02-10
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "TitleScreen.hpp"
#include <iostream>

TitleScreen::TitleScreen()
// : button_{}
{
  button_ = { .x = 200, .y = 200, .w = 200, .h = 60 };
  col_ = { .r = 0xFF, .g = 0x00, .b = 0x00, .a = SDL_ALPHA_OPAQUE };
}

TitleScreen::~TitleScreen() {}

void
TitleScreen::update(f64 delta)
{}

void
TitleScreen::render(SDL_Renderer* r)
{
  SDL_assert(SDL_SetRenderDrawColor(r, col_.r, col_.g, col_.b, col_.a) == 0 &&
             SDL_GetError());
  SDL_assert(col_.r == 0xFF);
  SDL_assert(SDL_RenderFillRect(r, &button_) == 0 && SDL_GetError());
}