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

//// Window
SDLW::Window::Window(const std::string& title,
                     i32 x,
                     i32 y,
                     i32 w,
                     i32 h,
                     u32 flags)
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

SDLW::Renderer::Renderer(SDLW::Window& window, i32 index, u32 flags)
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

// Renderer:Rect
void
SDLW::Renderer::RenderDrawRect(const SDLW::Rect& rect)
{
  if (SDL_RenderDrawRect(r_, &rect.r_) != 0)
    throw errors::sdl_error(SDL_GetError());
}

void
SDLW::Renderer::RenderFillRect(const SDLW::Rect& rect)
{
  if (SDL_RenderFillRect(r_, &rect.r_) != 0)
    throw errors::sdl_error(SDL_GetError());
}

// Renderer
void
SDLW::Renderer::RenderDrawLineF(f32 x1, f32 y1, f32 x2, f32 y2)
{

  if (SDL_RenderDrawLineF(r_, x1, y1, x2, y2) != 0)
    throw errors::sdl_error(SDL_GetError());
}

void
SDLW::Renderer::RenderDrawLine(i32 x1, i32 y1, i32 x2, i32 y2)
{
  if (SDL_RenderDrawLine(r_, x1, y1, x2, y2) != 0)
    throw errors::sdl_error(SDL_GetError());
}

// Renderer:utils
void
SDLW::Renderer::SetRenderDrawColor(u8 r, u8 g, u8 b, u8 a)
{
  if (SDL_SetRenderDrawColor(r_, r, g, b, a) != 0)
    throw errors::sdl_error(SDL_GetError());
}

void
SDLW::Renderer::RenderPresent()
{
  SDL_RenderPresent(r_);
}

void
SDLW::Renderer::RenderClear()
{
  SDL_RenderClear(r_);
}

// SDL Setup methods

void
SDLW::Init(u32 flags)
{
  if (SDL_Init(flags) != 0)
    throw errors::sdl_error(SDL_GetError());
}

void
SDLW::Quit()
{
  SDL_Quit();
}
