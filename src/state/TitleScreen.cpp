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
  // SDL_assert(SDL_SetRenderDrawColor(renderer, col_.renderer, col_.g, col_.b,
  // col_.a) == 0

  // TODO: Oui
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, col_.a);
  SDL_RenderClear(renderer);
}

void
TitleScreen::processEvent(SDL_Event event, SceneManager& sm)
{
  // set_next_state
  if (event.key.keysym.sym == SDLK_SPACE) {
    std::cout << "[Debug]: SPACE pressed while at TitleScreen" << std::endl;
    sm.set_next_state(STATE_GAME_SCENE);
  }
}
