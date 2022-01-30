#pragma once

#include "SDL2/SDL.h"

class Renderer
{
private:
  SDL_Window* w_;
  SDL_Renderer* r_;

public:
  Renderer();
  ~Renderer();

  void clear();
  void draw();
};
