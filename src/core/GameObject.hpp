//
// Created by massimo on 23/03/2022.
//

#ifndef TEMPEST_ATARI_GAMEOBJECT_HPP
#define TEMPEST_ATARI_GAMEOBJECT_HPP

#include <SDL2/SDL_render.h>
#include "../utils/types.hpp"
#include "Map.hpp"
#include "../utils/Delay.hpp"

enum e_direction {
  NONE, LEFT, RIGHT, FORWARD, BACKWARD
};

class GameObject
{
protected:
  static constexpr f64 MOVE_DELAY_ = 50;
  u8 band_num_ = 0;
  bool active_ = true;
  f32 progress_ = 0;
  enum e_direction moving_direction_{NONE};
  Delay move_delay_{MOVE_DELAY_};
  SDL_Rect collider_;  // todo: init

  void move(f64 delta, const Map &map);

public:
  GameObject() = default;
  GameObject(u8 band_num, bool active, f32 progress, e_direction moving_direction, f64 move_delay);
  GameObject(const GameObject &go) = default;
  virtual ~GameObject() = default;

  bool isActive() const;
  u8 getBandNum() const;
  void setMovingDirection(e_direction moving_direction);
  void setMoveDelay(f64 moveDelay);
  void activate(u8 band_num, f32 progress, e_direction moving_direction, f64 move_delay);
  void deactivate();
  bool isColliding(const GameObject &go) const;
  virtual void update(f64 delta, const Map &map) = 0;
  virtual void render(SDL_Renderer *renderer, const Map &map) const = 0;
};

#endif // TEMPEST_ATARI_GAMEOBJECT_HPP
