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

#include "../sdlw/SDLW.hpp"
#include "../utils/types.hpp"
#include "SDL2/SDL.h"
#include <memory>

class Renderer // TODO: change confusing name
{
private:
  std::unique_ptr<SDLW::Window> w_;
  std::unique_ptr<SDLW::Renderer> r_;

public:
  Renderer(u16 w_width, u16 w_height);
  ~Renderer();

  void clear();
  void draw();

  SDLW::Renderer& get_renderer();
};

#endif