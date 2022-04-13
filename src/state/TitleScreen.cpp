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
#include "../ui/Pen.hpp"
#include "SceneManager.hpp"
#include <iostream>

TitleScreen::TitleScreen()
// : button_{}
{
  col_ = { .r = 0xFF, .g = 0x00, .b = 0x00, .a = SDL_ALPHA_OPAQUE };
}

TitleScreen::~TitleScreen() {}

void
TitleScreen::update(f64 delta, SceneManager& sm)
{}

void
TitleScreen::render(SDL_Renderer* renderer) const
{
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, col_.a);
  SDL_RenderClear(renderer);

  // Draw text
  // TODO: remove hardcoded WINDOWS_WIDTH
  std::string tempest_s{ "TEMPEST" };
  std::string play{ "Press space to play!" };
  std::string authors{ "Massimo Venuti - Tarek Kunze" };
  Pen::draw_string(
    tempest_s, 960 / 2 - Pen::get_string_width(tempest_s) / 2, 160, renderer);
  Pen::draw_string(
    play, 960 / 2 - Pen::get_string_width(play) / 2, 300, renderer);
  Pen::draw_string(
    authors, 960 / 2 - Pen::get_string_width(authors) / 2, 550, renderer);
}

void
TitleScreen::processEvent(SDL_Event event, SceneManager& sm)
{
  // set_next_state
  if (event.key.keysym.sym == SDLK_SPACE) {
    std::cout << "[Debug]: SPACE pressed while at TitleScreen" << std::endl;
    sm.set_next_state(STATE_LEVEL_SELECT);
  }
}
