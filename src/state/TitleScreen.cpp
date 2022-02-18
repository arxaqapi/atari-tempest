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
  col_ = { .r = 0xFF, .g = 0x00, .b = 0x00, .a = SDL_ALPHA_OPAQUE };
}

TitleScreen::~TitleScreen() {}

void
TitleScreen::update(f64 delta)
{}

void
TitleScreen::render(SDL_Renderer* r)
{
  // SDL_assert(SDL_SetRenderDrawColor(r, col_.r, col_.g, col_.b, col_.a) == 0
  // &&
  //  SDL_GetError());
  // SDL_assert(col_.r == 0xFF);
  // SDL_assert(SDL_RenderFillRect(r, &button_) == 0 && SDL_GetError());

  // TODO: render cube centered
  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0xFF, col_.a);
  SDL_Rect outter_rec = { .x = 250, .y = 150, .w = 500, .h = 300 };
  SDL_RenderDrawRect(r, &outter_rec);
  // TODO: render smaller cube centered
  // SDL_SetRenderDrawColor(r, 0xAA, 0x00, 0xFF, col_.a);
  // SDL_Rect inner_rec = { .x = 350, .y = 250, .w = 300, .h = 100 };
  // SDL_RenderDrawRect(r, &inner_rec);
  // TODO: render lines to make a pipe
  // SDL_RenderDrawLine(r, 250, 150, 350, 250);
  // SDL_RenderDrawLine(r, 750, 150, 650, 250);
  // SDL_RenderDrawLine(r, 250, 450, 350, 350);
  // SDL_RenderDrawLine(r, 750, 450, 650, 350);

  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, col_.a);
  SDL_RenderDrawLine(r, 0, 0, 1000 / 2, 600 / 2);
}