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

#include "SDL2/SDL.h"
#include <string>
#include "../utils/types.hpp"

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
  Rect(int x, int y, int w, int h);
  ~Rect();

  int x();
  int y();
  int w();
  int h();
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
  Window(const std::string& title, int x, int y, int w, int h, Uint32 flags);
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
  Renderer(SDLW::Window& window, int index, Uint32 flags);
  ~Renderer();

  void RenderDrawRect(const SDLW::Rect& rect);
  void RenderFillRect(const SDLW::Rect& rect);

  void RenderDrawLineF(f32 x1, f32 y1, f32 x2, f32 y2);
  void RenderDrawLine(i32 x1, i32 y1, i32 x2, i32 y2);

  void SetRenderDrawColor(u8 r, u8 g, u8 b, u8 a);
  void RenderPresent();
  void RenderClear();

  // TODO: order and implement theses functions
  // struct SDL_FRect;
  // void SDL_RenderFillRectF();

};

void Init(u32 flags);
void Quit();

} // namespace SDLW


// SECTION: Extra
  // SDL_Color
  // SDL_GetTicks
  // SDL_GetPerformanceCounter
  // SDL_Delay()
  // struct SDL_Event; // override == operator 
  // SDL_Event SDL_PollEvent();


#endif