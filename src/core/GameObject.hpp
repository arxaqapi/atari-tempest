//
// Created by massimo on 23/03/2022.
//

#ifndef TEMPEST_ATARI_GAMEOBJECT_HPP
#define TEMPEST_ATARI_GAMEOBJECT_HPP

#include <SDL2/SDL_render.h>
#include "../utils/types.hpp"
#include "Map.hpp"

class GameObject
{
protected:
  u8 band_num_ = 0;
  f32 progress_ = 0;
  bool active_ = true;

public:
  GameObject() = default;
  GameObject(f32 progress);
  GameObject(const GameObject &go) = default;
  virtual ~GameObject() = default;

  bool isActive() const;
  u8 getBandNum() const;
  void moveLeft(const Map& map);
  void moveRight(const Map& map);
  void moveForward();
  void moveBackward();
  virtual void update(const Map &map) = 0;
  virtual void render(SDL_Renderer *renderer, const Map &map) const = 0;
};

#endif // TEMPEST_ATARI_GAMEOBJECT_HPP
