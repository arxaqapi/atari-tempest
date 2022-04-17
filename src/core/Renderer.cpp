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

#include "Renderer.hpp"
#include "../utils/Errors.hpp"
#include <iostream>

Renderer::Renderer(u16 w_width, u16 w_height)
{
  std::cout << "rend constr" << std::endl;

  // NOTE: to be replaced with wrapped methods and classes
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    throw errors::sdl_error(SDL_GetError());

  w_ = SDL_CreateWindow("Atari Tempest - VENUTI Massimo, Kunze Tarek",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        w_width,
                        w_height,
                        0);
  if (w_ == NULL)
    throw errors::sdl_error(SDL_GetError());
  r_ = SDL_CreateRenderer(w_, -1, 0);
  if (r_ == NULL)
    throw errors::sdl_error(SDL_GetError());
}

void
Renderer::clear()
{
  if (SDL_SetRenderDrawColor(r_, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE) != 0)
    throw errors::sdl_error(SDL_GetError());
  if (SDL_RenderClear(r_) != 0)
    throw errors::sdl_error(SDL_GetError());
}

void
Renderer::draw()
{
  SDL_RenderPresent(r_);
}

Renderer::~Renderer()
{
  std::cout << "rend destr" << std::endl;
  SDL_DestroyRenderer(r_);
  SDL_DestroyWindow(w_);
  SDL_Quit();
}

SDL_Renderer*
Renderer::get_renderer()
{
  return r_;
}
