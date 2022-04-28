#include "DeathScreen.hpp"
#include "../ui/Pen.hpp"
#include "SceneManager.hpp"

DeathScreen::DeathScreen() {}

DeathScreen::~DeathScreen() {}

void
DeathScreen::processEvent(SDL_Event* event, SceneManager& sm)
{
  if (event->type == SDL_KEYDOWN) {
    if (event->key.keysym.sym == SDLK_SPACE) {
      sm.setNextState(STATE_GAME_SCENE);
    } else if (event->key.keysym.sym == SDLK_RETURN) {
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
  Pen::drawStringCenteredInX("Game Over ...", 200, renderer);
  Pen::drawStringCenteredInX("[Space] to restart game", 400, renderer);
  Pen::drawStringCenteredInX(
    "[Enter] to go back to level select", 500, renderer);
}
