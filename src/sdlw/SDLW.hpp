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
namespace SDLW {
class Rect
{
private:
  SDL_Rect r_;

public:
  Rect() = delete;
  Rect(int x, int y, int w, int h);
  Rect(SDL_Rect* r);
  ~Rect();

  int x();
  int y();
  int w();
  int h();
  const SDL_Rect* get() const;
};

void
RenderDrawRect(SDL_Renderer* renderer, const SDLW::Rect& rect);

void
RenderFillRect(SDL_Renderer* renderer, const SDLW::Rect& rect);

/// Forward declaration
class Renderer;

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
};

} // namespace SDLW

#endif