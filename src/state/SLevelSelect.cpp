
#include "SLevelSelect.hpp"
#include <iostream>

SLevelSelect::SLevelSelect()
// : button_{}
{}

SLevelSelect::~SLevelSelect() {}

void
SLevelSelect::update(f64 delta)
{}

void
SLevelSelect::render(SDL_Renderer* r)
{
  SDL_SetRenderDrawColor(r, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(r);
  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(r, 0, 0, 1000 / 2, 600 / 2);
}