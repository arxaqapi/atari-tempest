//
// Created by massimo on 24/03/2022.
//

#ifndef TEMPEST_ATARI_BULLET_HPP
#define TEMPEST_ATARI_BULLET_HPP

#include "../sdlw/SDLW.hpp"
#include "GameObject.hpp"

/**
 * @brief Représente une balle
 */
class Bullet : public GameObject
{
public:
  Bullet();
  Bullet(const Bullet& bullet) = default;
  ~Bullet() override = default;

  void update(f64 delta, const Map& map) override;
  void render(SDLW::Renderer& renderer,
              const Map& map,
              const color& render_color) const override;
};

#endif // TEMPEST_ATARI_BULLET_HPP
