
#include "LevelSelectionScene.hpp"
#include <iostream>

LevelSelectionScene::LevelSelectionScene()
// : button_{}
{}

LevelSelectionScene::~LevelSelectionScene() {}

void
LevelSelectionScene::update(f64 delta)
{}

void
LevelSelectionScene::render(SDL_Renderer* r)
{
  SDL_SetRenderDrawColor(r, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(r);
  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(r, 0, 0, 1000 / 2, 600 / 2);
}