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
public:
  Flipper();
  Flipper(u8 band_num);
  Flipper(const Flipper &flipper) = default;
  ~Flipper() override = default;

  void render(SDL_Renderer *renderer, const Map &map) const override;
  void update(const Map &map) override;
};

#endif // TEMPEST_ATARI_FLIPPER_HPP
