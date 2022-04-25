/**
 * @file TitleScreen.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-02-10
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef H_TEMPEST_GAME_INC_TITLESCREEN_
#define H_TEMPEST_GAME_INC_TITLESCREEN_

#include "Scene.hpp"

class SceneManager;

class TitleScreen : public Scene
{
private:
public:
  TitleScreen();
  ~TitleScreen();

  void processEvent(SDL_Event* event, SceneManager& sm) override;
  void update(f64 delta, SceneManager& sm) override;
  void render(SDLW::Renderer& renderer) const override;
};

#endif