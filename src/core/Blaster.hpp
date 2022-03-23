//
// Created by massimo on 23/03/2022.
//

#ifndef TEMPEST_ATARI_BLASTER_HPP
#define TEMPEST_ATARI_BLASTER_HPP

#include "GameObject.hpp"

class Blaster: public GameObject
{
public:
  Blaster() = default;
  Blaster(const Blaster &blaster) = default;
  ~Blaster() override = default;

  void render(SDL_Renderer *renderer, const Map &map) const override;
  void update(const Map& map) override;
};

#endif // TEMPEST_ATARI_BLASTER_HPP
