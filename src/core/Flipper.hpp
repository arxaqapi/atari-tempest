//
// Created by massimo on 23/03/2022.
//

#ifndef TEMPEST_ATARI_FLIPPER_HPP
#define TEMPEST_ATARI_FLIPPER_HPP

#include "../sdlw/SDLW.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
class Flipper : public GameObject
{
private:
  e_direction band_change_direction_ = RIGHT;

public:
  Flipper();
  Flipper(const Flipper& flipper) = default;
  ~Flipper() override = default;

  inline void setBandChangeDirection(e_direction band_change_direction)
  {
    band_change_direction_ = band_change_direction;
  }
  void render(SDLW::Renderer& renderer,
              const Map& map,
              const color& render_color) const override;
  void update(f64 delta, const Map& map) override;
  inline e_direction getBandChangeDirection() const
  {
    return band_change_direction_;
  }
};

#endif // TEMPEST_ATARI_FLIPPER_HPP
