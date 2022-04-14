/**
 * @file Game.cpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "Game.hpp"
#include <iostream>

Game::Game() {}

Game::~Game()
{
  std::cout << "Game Object destroyed" << std::endl;
}

void
Game::clear()
{
  r_.clear();
}

void
Game::process_events()
{
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        this->stop_();
        break;

      default:
        break;
    }
    switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        this->stop_();
        break;

      default:
        break;
    }
    sm_.get_current_scene().processEvent(event, sm_);
  }
  // const u8* keyboardState = SDL_GetKeyboardState(NULL);
  // if (keyboardState[SDL_SCANCODE_SPACE]) {
}

void
Game::update(f64 delta)
{
  sm_.update(delta);
}

void
Game::render()
{
  sm_.get_current_scene().render(r_.get_renderer());
  r_.draw();
}