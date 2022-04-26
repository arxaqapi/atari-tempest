#include "LevelSelectionScene.hpp"
#include "../core/FigureData.hpp"
#include "../ui/Pen.hpp"
#include "../ui/UILevelBox.hpp"
#include "../utils/types.hpp"
#include "SceneManager.hpp"
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;

LevelSelectionScene::LevelSelectionScene()
  : ui_level_carousel_{ 200, 390, 200, 200 }
{}

LevelSelectionScene::~LevelSelectionScene() {}

void
LevelSelectionScene::update(f64 delta, SceneManager& sm)
{}

void
LevelSelectionScene::render(SDLW::Renderer& renderer) const
{
  renderer.SetRenderDrawColor(0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  renderer.RenderClear();

  // Draw UI
  ui_level_carousel_.render(renderer);

  // Draw text
  Pen::draw_string("LEVEL", 60, 420, renderer);
  Pen::draw_string("HOLE ", 60, 458, renderer);
  Pen::draw_string("BONUS", 60, 495, renderer);

  Pen::draw_string_centered_x("Level selection scene", 100, renderer);
  Pen::draw_string_centered_x("Press space", 250, renderer);
}

void
LevelSelectionScene::processEvent(SDL_Event* event, SceneManager& sm)
{
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
      case SDLK_SPACE:
        ui_level_carousel_.select(sm);
        break;
      case SDLK_RIGHT:
        ui_level_carousel_.go_right();
        break;
      case SDLK_LEFT:
        ui_level_carousel_.go_left();
        break;
      default:
        break;
    }
  }
}
