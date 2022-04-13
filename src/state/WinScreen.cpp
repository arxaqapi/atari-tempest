#include "WinScreen.hpp"
#include "../ui/Pen.hpp"
#include "SceneManager.hpp"

WinScreen::WinScreen() {}

WinScreen::~WinScreen() {}

void
WinScreen::processEvent(SDL_Event event, SceneManager& sm)
{
  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
    std::cout << "[Space] pressed" << std::endl;
    sm.set_next_state(STATE_LEVEL_SELECT);
  }
}

void
WinScreen::update(f64 delta, SceneManager& sm)
{}

void
WinScreen::render(SDL_Renderer* renderer) const
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Draw text
  std::string win_msg{ "You won!" };
  Pen::draw_string(
    win_msg, 960 / 2 - Pen::get_string_width(win_msg) / 2, 200, renderer);

  std::string lselect_msg{ "Press space to go back to Level selection screen" };
  Pen::draw_string(lselect_msg,
                   960 / 2 - Pen::get_string_width(lselect_msg) / 2,
                   400,
                   renderer);
}
