#include "DeathScreen.hpp"
#include "../ui/Pen.hpp"
#include "SceneManager.hpp"

DeathScreen::DeathScreen() {}

DeathScreen::~DeathScreen() {}

void
DeathScreen::processEvent(SDL_Event event, SceneManager& sm)
{
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_SPACE) {
      sm.set_next_state(STATE_GAME_SCENE);
    } else if (event.key.keysym.sym == SDLK_RETURN) {
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
  std::string death_msg{ "Game Over ..." };
  Pen::draw_string(
    death_msg, 960 / 2 - Pen::get_string_width(death_msg) / 2, 200, renderer);

  std::string restart_msg{ "[Space] to restart game" };
  Pen::draw_string(restart_msg,
                   960 / 2 - Pen::get_string_width(restart_msg) / 2,
                   400,
                   renderer);

  std::string lselect_msg{ "[Enter] to go back to level select" };
  Pen::draw_string(lselect_msg,
                   960 / 2 - Pen::get_string_width(lselect_msg) / 2,
                   500,
                   renderer);
}
