/**
 * @file Scene.cpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-02-10
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */
#ifndef H_TEMPEST_GAME_INC_SCENE_
#define H_TEMPEST_GAME_INC_SCENE_

#include "../utils/types.hpp"
#include <vector>

#include <SDL2/SDL.h>

class Scene
{
private:
//  std::vector<Entity> enemies_;
//  Entity player_;

public:
  Scene() = default;
  Scene(const Scene & scene) = default;
  ~Scene() = default;

  virtual void processEvent(SDL_Event event) = 0;
  virtual void update(f64 delta) = 0;
  virtual void render(SDL_Renderer* renderer) const = 0;
};

#endif