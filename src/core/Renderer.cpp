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
#include <cassert>
#include <iostream>

Renderer::Renderer()
{
  std::cout << "rend constr" << std::endl;

  w_ = SDL_CreateWindow("Atari Tempest - Kunze Tarek",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        960,
                        540,
                        0);
  assert(w_ != NULL && SDL_GetError());
  r_ = SDL_CreateRenderer(w_, -1, 0);
  assert(r_ != NULL && SDL_GetError());
}

void
Renderer::clear()
{
  assert(SDL_SetRenderDrawColor(r_, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE) == 0 &&
         SDL_GetError());
  assert(SDL_RenderClear(r_) == 0 && SDL_GetError());
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
