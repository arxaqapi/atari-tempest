//
// Created by massimo on 16/04/2022.
//

#ifndef TEMPEST_ATARI_SPIKER_HPP
#define TEMPEST_ATARI_SPIKER_HPP

#include "GameObject.hpp"

/**
 * @brief Représente le Spiker
 */
class Spiker : public GameObject
{
public:
  Spiker();
  Spiker(const Spiker& spiker) = default;
  ~Spiker() override = default;

  void hit() override;
  void render(SDLW::Renderer& renderer,
              const Map& map,
              const color& render_color) const override;
  void update(f64 delta, const Map& map) override;
};

#endif // TEMPEST_ATARI_SPIKER_HPP
