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

TitleScreen::TitleScreen() {}

TitleScreen::~TitleScreen() {}

void
TitleScreen::update(f64, SceneManager&)
{}

void
TitleScreen::render(SDLW::Renderer& renderer) const
{
  renderer.SetRenderDrawColor(0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  renderer.RenderClear();

  // Draw text
  Pen::draw_string_centered_x("TEMPEST", 160, renderer, 4);
  Pen::draw_string_centered_x("Press space to play!", 300, renderer);
  Pen::draw_string_centered_x("Massimo Venuti - Tarek Kunze", 550, renderer);
}

void
TitleScreen::processEvent(SDL_Event* event, SceneManager& sm)
{
  // set_next_state
  if (event->key.keysym.sym == SDLK_SPACE) {
    std::cout << "[Debug]: SPACE pressed while at TitleScreen" << std::endl;
    sm.set_next_state(STATE_LEVEL_SELECT);
  }
}
