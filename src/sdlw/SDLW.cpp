/**
 * @file SDLW.cpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-15
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "SDLW.hpp"
#include "../utils/Errors.hpp"
#include <cassert>

SDLW::Rect::Rect(int x, int y, int w, int h)
  : r_{ x, y, w, h }
{}

SDLW::Rect::Rect(SDL_Rect* r)
  : r_{ r->x, r->y, r->w, r->h }
{}

SDLW::Rect::~Rect() {}

int
SDLW::Rect::x()
{
  return r_.x;
}
int
SDLW::Rect::y()
{
  return r_.y;
}
int
SDLW::Rect::w()
{
  return r_.w;
}
int
SDLW::Rect::h()
{
  return r_.h;
}
const SDL_Rect*
SDLW::Rect::get() const
{
  return &r_;
}

void
SDLW::RenderDrawRect(SDL_Renderer* renderer, const SDLW::Rect& rect)
{
  if (SDL_RenderDrawRect(renderer, rect.get()) != 0) {
    throw errors::sdl_error(SDL_GetError());
  }
}

void
SDLW::RenderFillRect(SDL_Renderer* renderer, const SDLW::Rect& rect)
{
  if (SDL_RenderFillRect(renderer, rect.get()) != 0) {
    throw errors::sdl_error(SDL_GetError());
  }
}

//// Window
SDLW::Window::Window(const std::string& title,
                     int x,
                     int y,
                     int w,
                     int h,
                     Uint32 flags)
{
  w_ = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
  if (w_ == NULL) {
    throw errors::sdl_error(SDL_GetError());
  }
}

SDLW::Window::~Window()
{
  SDL_DestroyWindow(w_);
}

//// Renderer

SDLW::Renderer::Renderer(SDLW::Window& window, int index, Uint32 flags)
{
  r_ = SDL_CreateRenderer(window.w_, index, flags);
  if (r_ == NULL) {
    throw errors::sdl_error(SDL_GetError());
  }
}

SDLW::Renderer::~Renderer()
{
  SDL_DestroyRenderer(r_);
}
