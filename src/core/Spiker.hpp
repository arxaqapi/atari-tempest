//
// Created by massimo on 16/04/2022.
//

#ifndef TEMPEST_ATARI_SPIKER_HPP
#define TEMPEST_ATARI_SPIKER_HPP

#include "GameObject.hpp"
class Spiker : public GameObject
{
public:
  Spiker();
  Spiker(const Spiker& spiker) = default;
  ~Spiker() override = default;

  void render(SDL_Renderer* renderer, const Map& map) const override;
  void update(f64 delta, const Map& map) override;

};

#endif // TEMPEST_ATARI_SPIKER_HPP
