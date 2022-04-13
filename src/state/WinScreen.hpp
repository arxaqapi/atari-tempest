/**
 * @file WinScreen.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-13
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef H_TEMPEST_GAME_WINSCREEN_TITLESCREEN_
#define H_TEMPEST_GAME_WINSCREEN_TITLESCREEN_

#include "Scene.hpp"

class SceneManager;

class WinScreen : public Scene
{
private:
public:
  WinScreen();
  ~WinScreen();

  void processEvent(SDL_Event event, SceneManager& sm) override;
  void update(f64 delta, SceneManager& sm) override;
  void render(SDL_Renderer* renderer) const override;
};

#endif