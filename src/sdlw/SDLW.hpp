/**
 * @file SDLW.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-15
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */
#ifndef TEMPEST_ATARI_SDLW_HPP
#define TEMPEST_ATARI_SDLW_HPP

#include "../utils/types.hpp"
#include "SDL2/SDL.h"
#include <string>

namespace SDLW {
/// Forward declaration
class Renderer;

class Rect
{
  friend class Renderer;

private:
  SDL_Rect r_;

public:
  Rect() = delete;
  Rect(i32 x, i32 y, i32 w, i32 h);
  ~Rect();

  i32 x() const;
  i32 y() const;
  i32 w() const;
  i32 h() const;
};

//// Window

class Window
{
  friend class Renderer;

private:
  SDL_Window* w_;

public:
  Window() = delete;
  Window(const SDLW::Window&) = delete;
  Window(const std::string& title, i32 x, i32 y, i32 w, i32 h, u32 flags);
  ~Window();
};

//// Renderer
class Renderer
{
private:
  SDL_Renderer* r_;

public:
  Renderer() = delete;
  Renderer(const SDLW::Renderer&) = delete;
  Renderer(SDLW::Window& window, i32 index, u32 flags);
  ~Renderer();

  void RenderDrawRect(const SDLW::Rect& rect);
  void RenderFillRect(const SDLW::Rect& rect);

  void RenderDrawLineF(f32 x1, f32 y1, f32 x2, f32 y2);
  void RenderDrawLine(i32 x1, i32 y1, i32 x2, i32 y2);

  void SetRenderDrawColor(u8 r, u8 g, u8 b, u8 a);
  void RenderPresent();
  void RenderClear();

  // TODO: order and implement theses functions
  // void SDL_RenderFillRectF();
};

void
Init(u32 flags);
void
Quit();

// Time
u64
GetTicks64();
u64
GetPerformanceCounter();
void
Delay(u32 ms);
u64
GetPerformanceFrequency();

} // namespace SDLW

// SECTION: Extra
// struct SDL_FRect;
// SDL_Color
// struct SDL_Event; // override == operator
// SDL_Event SDL_PollEvent();

#endif