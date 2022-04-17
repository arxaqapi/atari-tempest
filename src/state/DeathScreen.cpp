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
      sm.set_next_state(STATE_GAME_SCENE);
    } else if (event->key.keysym.sym == SDLK_RETURN) {
      sm.set_next_state(STATE_LEVEL_SELECT);
    }
  }
}

void
DeathScreen::update(f64 delta, SceneManager& sm)
{}

void
DeathScreen::render(SDL_Renderer* renderer) const
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Draw text
  Pen::draw_string_centered_x("Game Over ...", 200, renderer);
  Pen::draw_string_centered_x("[Space] to restart game", 400, renderer);
  Pen::draw_string_centered_x(
    "[Enter] to go back to level select", 500, renderer);
}
