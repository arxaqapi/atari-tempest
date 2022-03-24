//
// Created by massimo on 24/03/2022.
//

#ifndef TEMPEST_ATARI_BULLET_HPP
#define TEMPEST_ATARI_BULLET_HPP

#include "GameObject.hpp"
class Bullet : public GameObject
{
public:
  Bullet() = default;
  explicit Bullet(u8 band_num);
  Bullet(const Bullet &bullet) = default;
  ~Bullet() override = default;

  void activate(u8 band_num);
  void update(const Map &map) override;
  void render(SDL_Renderer *renderer, const Map &map) const override;
};

#endif // TEMPEST_ATARI_BULLET_HPP
