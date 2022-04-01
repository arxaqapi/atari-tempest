
#include "LevelSelectionScene.hpp"

LevelSelectionScene::LevelSelectionScene()
// : button_{}
{}

LevelSelectionScene::~LevelSelectionScene() {}

void
LevelSelectionScene::update(f64 delta, SceneManager& sm)
{}

void
LevelSelectionScene::render(SDL_Renderer* renderer) const
{
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(renderer, 0, 0, 1000 / 2, 600 / 2);
}

void
LevelSelectionScene::processEvent(SDL_Event event, SceneManager& sm)
{}
