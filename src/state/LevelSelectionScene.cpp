/**
 * @file LevelSelectionScene.cpp
 * @author Massimo, Tarek Kunze (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */
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
  Pen::drawString("LEVEL", 60, 420, renderer, color{ 0x00, 0xFF, 0x00 });
  Pen::drawString("HOLE ", 60, 458, renderer, color{ 0x00, 0xFF, 0x00 });
  Pen::drawString("BONUS", 60, 495, renderer, color{ 0x00, 0xFF, 0x00 });

  Pen::drawStringCenteredInX("Joueur I", 150, renderer, 1.6);
  Pen::drawStringCenteredInX("Fleches directionnelles pour le choix du niveau",
                             230,
                             renderer,
                             0.90,
                             color{ 0x00, 0xFF, 0xFF });
  Pen::drawStringCenteredInX(
    "[Espace] pour jouer", 275, renderer, color{ 0xF8, 0xEA, 0x8C });
}

void
LevelSelectionScene::processEvent(const SDLW::Event& event, SceneManager& sm)
{
  if (event.getType() == SDL_KEYDOWN) {
    switch (event.getKeycode()) {
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
