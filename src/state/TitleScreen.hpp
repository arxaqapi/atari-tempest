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

class TitleScreen : public Scene
{
private:
  SDL_Color col_;

public:
  TitleScreen();
  ~TitleScreen();

  void processEvent(SDL_Event event) override;
  void update(f64 delta) override;
  void render(SDL_Renderer* renderer) const override;
};

#endif