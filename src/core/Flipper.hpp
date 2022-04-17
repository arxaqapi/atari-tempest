//
// Created by massimo on 23/03/2022.
//

#ifndef TEMPEST_ATARI_FLIPPER_HPP
#define TEMPEST_ATARI_FLIPPER_HPP

#include "GameObject.hpp"
#include "Map.hpp"
#include <SDL2/SDL_render.h>
class Flipper : public GameObject
{
private:
  Delay band_change_delay_{750};
  e_direction band_change_direction_ = RIGHT;

public:
  Flipper();
  Flipper(const Flipper& flipper) = default;
  ~Flipper() override = default;

  inline void setBandChangeDirection(e_direction bandChangeDirection)
  {
    band_change_direction_ = bandChangeDirection;
  }
  void render(SDL_Renderer* renderer, const Map& map) const override;
  void update(f64 delta, const Map& map) override;
};

#endif // TEMPEST_ATARI_FLIPPER_HPP
