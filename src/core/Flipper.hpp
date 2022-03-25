//
// Created by massimo on 23/03/2022.
//

#ifndef TEMPEST_ATARI_FLIPPER_HPP
#define TEMPEST_ATARI_FLIPPER_HPP

#include <SDL2/SDL_render.h>
#include "Map.hpp"
#include "GameObject.hpp"
class Flipper: public GameObject
{
private:
  f64 STAGE_2_MOVING_DELAY_ = 500;

public:
  Flipper();
  explicit Flipper(u8 band_num);
  Flipper(const Flipper &flipper) = default;
  ~Flipper() override = default;

  void activate(u8 band_num);
  void render(SDL_Renderer *renderer, const Map &map) const override;
  void update(f64 delta, const Map &map) override;
};

#endif // TEMPEST_ATARI_FLIPPER_HPP
