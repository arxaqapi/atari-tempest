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

} // namespace SDLW

#endif