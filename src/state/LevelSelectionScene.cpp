#include "LevelSelectionScene.hpp"
#include "../ui/Pen.hpp"
#include "SceneManager.hpp"

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

  // Draw text
  std::string level_selection{ "Level selection scene" };
  std::string play_msg{ "Press space" };
  Pen::draw_string(level_selection,
                   960 / 2 - Pen::get_string_width(level_selection) / 2,
                   200,
                   renderer);
  Pen::draw_string(
    play_msg, 960 / 2 - Pen::get_string_width(play_msg) / 2, 350, renderer);
}

void
LevelSelectionScene::processEvent(SDL_Event event, SceneManager& sm)
{
  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
    std::cout << "[Space] pressed" << std::endl;
    sm.set_next_state(STATE_GAME_SCENE);
  }
}
