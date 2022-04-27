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

u16 Game::WINDOWS_WIDTH_ = 960;

u16 Game::WINDOWS_HEIGHT_ = 540;

Game::Game() {}

Game::Game(u16 w_width, u16 w_height)
  : r_{ w_width, w_height }
{
  WINDOWS_WIDTH_ = w_width;
  WINDOWS_HEIGHT_ = w_height;
}

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
    sm_.get_current_scene().processEvent(&event, sm_);
  }
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

u16
Game::get_width()
{
  return Game::WINDOWS_WIDTH_;
}

u16
Game::get_height()
{
  return Game::WINDOWS_HEIGHT_;
}
