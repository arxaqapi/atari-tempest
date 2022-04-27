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
#include "../ui/Pen.hpp"
#include <iostream>

using namespace std::string_literals;

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
      case SDL_KEYDOWN: {
        if (event.key.keysym.sym == SDLK_d) {
          std::cout << "[Log] - Debug overlay activated" << std::endl;
          debug_flag_ = !debug_flag_;
        }
        break;
      }
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
  if (debug_flag_) {
    Pen::draw_string("IFD: "s + std::to_string(debug_val_.inter_frame_delay_),
                     763 - 300,
                     30,
                     r_.get_renderer(),
                     color{ 0xFF, 0, 0 });
    Pen::draw_string("FPS: "s + std::to_string(debug_val_.fps_),
                     763 - 300,
                     60,
                     r_.get_renderer(),
                     color{ 0xFF, 0, 0 });
  }
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

void
Game::debug_set_interframe_delay(f64 inter_frame_delay)
{
  debug_val_.inter_frame_delay_ = inter_frame_delay;
}

void
Game::debug_set_fps(f64 fps)
{
  debug_val_.fps_ = fps;
}
