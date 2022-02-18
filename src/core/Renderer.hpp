/**
 * @file Renderer.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */
#ifndef H_TEMPEST_GAME_INC_RENDERER_
#define H_TEMPEST_GAME_INC_RENDERER_

#include "../utils/types.hpp"
#include "SDL2/SDL.h"

class Renderer
{
private:
  SDL_Window* w_;
  SDL_Renderer* r_;

public:
  Renderer(u16 w_width, u16 w_height);
  ~Renderer();

  void clear();
  void draw();

  SDL_Renderer* get_renderer();
};

#endif