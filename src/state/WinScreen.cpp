/**
 * @file WinScreen.cpp
 * @author Tarek Kunze (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "WinScreen.hpp"
#include "../ui/Pen.hpp"
#include "SceneManager.hpp"

WinScreen::WinScreen() {}

WinScreen::~WinScreen() {}

void
WinScreen::processEvent(const SDLW::Event& event, SceneManager& sm)
{
  if (event.getType() == SDL_KEYDOWN && event.getKeycode() == SDLK_SPACE) {
    sm.setNextState(STATE_LEVEL_SELECT);
  }
}

void
WinScreen::update(f64, SceneManager&)
{}

void
WinScreen::render(SDLW::Renderer& renderer) const
{
  renderer.SetRenderDrawColor(0, 0, 0, 255);
  renderer.RenderClear();

  // Draw text
  Pen::drawStringCenteredInX(
    "Vous avez Gagne!", 200, renderer, 2, color{ 0, 255, 0 });
  Pen::drawStringCenteredInX("[Espace] Pour revenir", 400, renderer);
  Pen::drawStringCenteredInX("a la selection de niveau", 438, renderer);
}
