//
// Created by massimo on 23/03/2022.
//

#ifndef TEMPEST_ATARI_GAMEOBJECT_HPP
#define TEMPEST_ATARI_GAMEOBJECT_HPP

#include "../utils/Delay.hpp"
#include "../utils/Utils.hpp"
#include "../utils/types.hpp"
#include "Map.hpp"
#include <SDL2/SDL_render.h>

enum e_direction
{
  NONE,
  LEFT,
  RIGHT,
  FORWARD,
  BACKWARD
};

class GameObject
{
protected:
  u8 band_num_ = 0;
  bool active_ = true;
  f32 progress_ = 0;
  f32 progress_velocity_ = 0.0005;
  enum e_direction moving_direction_
  {
    NONE
  };
  Delay move_delay_{ 50 };

  void move(f64 delta, const Map& map);

public:
  GameObject() = default;
  GameObject(const GameObject& go) = default;
  virtual ~GameObject() = default;

  bool isActive() const;
  u8 getBandNum() const;
  void setMovingDirection(e_direction moving_direction);
  void setMoveDelay(f64 moveDelay);
  inline void setProgress(f32 progress) { progress_ = progress; }
  inline f32 getProgress() const { return progress_; }
  void activate(u8 band_num,
                f32 progress,
                f32 progress_velocity,
                e_direction moving_direction,
                f64 move_delay);
  void deactivate();
  bool isColliding(const GameObject& go) const;
  virtual void hit();
  virtual void update(f64 delta, const Map& map) = 0;
  virtual void render(SDL_Renderer* renderer, const Map& map) const = 0;
};

#endif // TEMPEST_ATARI_GAMEOBJECT_HPP
