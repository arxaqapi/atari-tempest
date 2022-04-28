/**
 * @file Bullet.hpp
 * @author massimo
 * @version 0.1
 * @date 2022-03-24
 *
 * @copyright Copyright (c) 2022
 */

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
  Bullet() { deactivate(); }
  Bullet(const Bullet& bullet) = default;
  ~Bullet() override = default;

  void update(f64 delta, const Map& map) override;
  void render(SDLW::Renderer& renderer,
              const Map& map,
              const color& render_color) const override;
};

#endif // TEMPEST_ATARI_BULLET_HPP
