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
  f32 front_progression_ = 0;
  f32 lateral_progression_ = 0;
  f32 front_velocity_ = 0.0005;
  f32 lateral_velocity_ = 0.02;
  enum e_direction moving_direction_
  {
    NONE
  };

  void move(f64 delta, const Map& map);

public:
  GameObject() = default;
  GameObject(const GameObject& go) = default;
  virtual ~GameObject() = default;

  bool isActive() const;
  u8 getBandNum() const;
  void setMovingDirection(e_direction moving_direction);
  inline void setFrontProgression(f32 front_progression)
  {
    front_progression_ = front_progression;
  }
  inline f32 getFrontProgression() const { return front_progression_; }
  void activate(u8 band_num,
                f32 front_progression,
                f32 lateral_progression,
                f32 front_velocity,
                f32 lateral_velocity,
                e_direction moving_direction);
  void deactivate();
  bool isColliding(const GameObject& go) const;
  virtual void hit();
  virtual void update(f64 delta, const Map& map) = 0;
  virtual void render(SDL_Renderer* renderer, const Map& map, const color& render_color) const = 0;
};

#endif // TEMPEST_ATARI_GAMEOBJECT_HPP
