#include "LevelSelectionScene.hpp"
#include "../ui/Pen.hpp"
#include "../ui/UILevelBox.hpp"
#include "../utils/types.hpp"
#include "SceneManager.hpp"
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;

LevelSelectionScene::LevelSelectionScene() {}

LevelSelectionScene::~LevelSelectionScene() {}

void
LevelSelectionScene::update(f64, SceneManager&)
{}

void
LevelSelectionScene::render(SDLW::Renderer& renderer) const
{
  renderer.SetRenderDrawColor(0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  renderer.RenderClear();

  // Draw UI
  ui_level_carousel_.render(renderer);

  // Draw text
  Pen::draw_string("LEVEL", 60, 420, renderer, color{ 0x00, 0xFF, 0x00 });
  Pen::draw_string("HOLE ", 60, 458, renderer, color{ 0x00, 0xFF, 0x00 });
  Pen::draw_string("BONUS", 60, 495, renderer, color{ 0x00, 0xFF, 0x00 });

  Pen::draw_string_centered_x("Joueur I", 150, renderer, 1.6);
  Pen::draw_string_centered_x("Fleches directionnelles pour le choix du niveau",
                              230,
                              renderer,
                              0.90,
                              color{ 0x00, 0xFF, 0xFF });
  Pen::draw_string_centered_x(
    "[Espace] pour jouer", 275, renderer, color{ 0xF8, 0xEA, 0x8C });
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
