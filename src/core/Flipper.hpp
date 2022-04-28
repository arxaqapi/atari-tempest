/**
 * @file Flipper.hpp
 * @author massimo
 * @version 0.1
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2022
 */

#ifndef TEMPEST_ATARI_FLIPPER_HPP
#define TEMPEST_ATARI_FLIPPER_HPP

#include "../sdlw/SDLW.hpp"
#include "GameObject.hpp"
#include "Map.hpp"

/**
 * @brief Représente le Flipper
 */
class Flipper : public GameObject
{
private:
  /**
   * Direction pour le changement de bande
   */
  e_direction band_change_direction_ = RIGHT;

public:
  Flipper() { deactivate(); }
  Flipper(const Flipper& flipper) = default;
  ~Flipper() override = default;

  void render(SDLW::Renderer& renderer,
              const Map& map,
              const color& render_color) const override;
  void update(f64 delta, const Map& map) override;

  /**
   * Setters
   */
  inline void setBandChangeDirection(e_direction band_change_direction)
  {
    band_change_direction_ = band_change_direction;
  }

  /**
   * Getters
   */
  inline e_direction getBandChangeDirection() const
  {
    return band_change_direction_;
  }
};

#endif // TEMPEST_ATARI_FLIPPER_HPP
