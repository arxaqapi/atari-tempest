/**
 * @file SDLW.cpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
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
    throw errors::SdlError(SDL_GetError());
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
    throw errors::SdlError(SDL_GetError());
  }
}

SDLW::Renderer::~Renderer()
{
  SDL_DestroyRenderer(r_);
}

// Renderer:Rect
void
SDLW::Renderer::RenderDrawRect(const SDLW::Rect_T<i32>& rect)
{
  if (SDL_RenderDrawRect(r_, &rect.r_) != 0)
    throw errors::SdlError(SDL_GetError());
}

void
SDLW::Renderer::RenderFillRect(const SDLW::Rect_T<i32>& rect)
{
  if (SDL_RenderFillRect(r_, &rect.r_) != 0)
    throw errors::SdlError(SDL_GetError());
}

void
SDLW::Renderer::RenderFillRectF(const SDLW::Rect_T<f32>& rect)
{
  if (SDL_RenderFillRectF(r_, &rect.r_) != 0)
    throw errors::SdlError(SDL_GetError());
}

// Renderer
void
SDLW::Renderer::RenderDrawLineF(f32 x1, f32 y1, f32 x2, f32 y2)
{

  if (SDL_RenderDrawLineF(r_, x1, y1, x2, y2) != 0)
    throw errors::SdlError(SDL_GetError());
}

void
SDLW::Renderer::RenderDrawLine(i32 x1, i32 y1, i32 x2, i32 y2)
{
  if (SDL_RenderDrawLine(r_, x1, y1, x2, y2) != 0)
    throw errors::SdlError(SDL_GetError());
}

// Renderer:utils
void
SDLW::Renderer::SetRenderDrawColor(u8 r, u8 g, u8 b, u8 a)
{
  if (SDL_SetRenderDrawColor(r_, r, g, b, a) != 0)
    throw errors::SdlError(SDL_GetError());
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
    throw errors::SdlError(SDL_GetError());
}

void
SDLW::Quit()
{
  SDL_Quit();
}

// Time

u64
SDLW::GetTicks64()
{
#if SDL_MAJOR_VERSION >= 2 &&                                                  \
  ((SDL_MINOR_VERSION == 0 && SDL_PATCHLEVEL >= 18) ||                         \
   (SDL_MINOR_VERSION > 0 && SDL_PATCHLEVEL >= 0))
  return SDL_GetTicks64();
#else
  return SDL_GetTicks();
#endif
}

u64
SDLW::GetPerformanceCounter()
{
  return SDL_GetPerformanceCounter();
}

void
SDLW::Delay(u32 ms)
{
  SDL_Delay(ms);
}

u64
SDLW::GetPerformanceFrequency()
{
  return SDL_GetPerformanceFrequency();
}

// Events

SDLW::Event::Event() {}

SDLW::Event::~Event() {}

u32
SDLW::Event::getType() const
{
  return event_.type;
}

SDL_Keycode
SDLW::Event::getKeycode() const
{
  return event_.key.keysym.sym;
}

i32
SDLW::PollEvent(SDLW::Event& e)
{
  return SDL_PollEvent(&e.event_);
}

i32
SDLW::PollEvent()
{
  return SDL_PollEvent(nullptr);
}