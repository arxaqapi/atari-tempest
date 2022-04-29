/**
 * @file DeathScreen.cpp
 * @author Tarek Kunze (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */
#include "DeathScreen.hpp"
#include "../ui/Pen.hpp"
#include "SceneManager.hpp"

DeathScreen::DeathScreen() {}

DeathScreen::~DeathScreen() {}

void
DeathScreen::processEvent(const SDLW::Event& event, SceneManager& sm)
{
  if (event.getType() == SDL_KEYDOWN) {
    if (event.getKeycode() == SDLK_SPACE) {
      sm.setNextState(STATE_GAME_SCENE);
    } else if (event.getKeycode() == SDLK_RETURN) {
      sm.setNextState(STATE_LEVEL_SELECT);
    }
  }
}

void
DeathScreen::update(f64, SceneManager&)
{}

void
DeathScreen::render(SDLW::Renderer& renderer) const
{
  renderer.SetRenderDrawColor(0, 0, 0, 255);
  renderer.RenderClear();

  // Draw text
  Pen::drawStringCenteredInX(
    "Vous etes mort ...", 200, renderer, 2, color{ 255, 0, 0 });
  Pen::drawStringCenteredInX(
    "[Espace] pour relancer depuis le debut", 400, renderer);
  Pen::drawStringCenteredInX("[Entrez] Pour revenir", 500, renderer);
  Pen::drawStringCenteredInX("a la selection de niveau", 538, renderer);
}
