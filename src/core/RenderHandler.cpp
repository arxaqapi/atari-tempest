/**
 * @file Renderer.cpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "RenderHandler.hpp"
#include "../utils/Errors.hpp"
#include <iostream>

RenderHandler::RenderHandler(u16 w_width, u16 w_height)
{
  std::cout << "rend constr" << std::endl;

  SDLW::Init(SDL_INIT_VIDEO);

  w_ = std::make_unique<SDLW::Window>(
    "Atari Tempest - VENUTI Massimo, Kunze Tarek",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    w_width,
    w_height,
    0);
  r_ = std::make_unique<SDLW::Renderer>(*w_, -1, 0);
}

void
RenderHandler::clear()
{
  (*r_).SetRenderDrawColor(0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
  (*r_).RenderClear();
}

void
RenderHandler::draw()
{
  (*r_).RenderPresent();
}

RenderHandler::~RenderHandler()
{
  std::cout << "rend destr" << std::endl;
  SDLW::Quit();
  SDL_Quit();
}

SDLW::Renderer&
RenderHandler::get_renderer()
{
  return *r_;
}
