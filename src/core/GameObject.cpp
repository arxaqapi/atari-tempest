/**
 * @file GameObject.cpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "GameObject.hpp"
#include "../utils/types.hpp"
#include <cassert>
#include <iostream>

#include "TitleScreen.hpp"


GameObject::GameObject()
  : active_scene_{ new TitleScreen() }
{}

GameObject::~GameObject()
{
  std::cout << "GO destr" << std::endl;
}

void
GameObject::init()
{
  assert(SDL_Init(SDL_INIT_VIDEO) == 0 && SDL_GetError());
  assert(SDL_WasInit(SDL_INIT_VIDEO) != 0 && SDL_GetError());

  std::cout << "GO init" << std::endl;
  run_ = true;
}

void
GameObject::clear()
{
  r_.clear();
}

void
GameObject::process_events()
{
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        this->stop_();
        break;

      default:
        break;
    }
    switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        this->stop_();
        break;

      default:
        break;
    }
  }
  // const u8* keyboardState = SDL_GetKeyboardState(NULL);
  // if (keyboardState[SDL_SCANCODE_SPACE]) {
}

void
GameObject::update_state(f64 delta)
{
  active_scene_->update(delta);
}

void
GameObject::render()
{
  active_scene_->render(r_.get_renderer());
  r_.draw();
}