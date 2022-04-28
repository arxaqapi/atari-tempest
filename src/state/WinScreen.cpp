#include "WinScreen.hpp"
#include "../ui/Pen.hpp"
#include "SceneManager.hpp"

WinScreen::WinScreen() {}

WinScreen::~WinScreen() {}

void
WinScreen::processEvent(const SDLW::Event& event, SceneManager& sm)
{
  if (event.getType() == SDL_KEYDOWN && event.getKeycode() == SDLK_SPACE) {
    std::cout << "[Space] pressed" << std::endl;
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
  Pen::drawStringCenteredInX("You won!", 200, renderer);
  Pen::drawStringCenteredInX(
    "Press space to go back to Level selection screen", 400, renderer);
}
