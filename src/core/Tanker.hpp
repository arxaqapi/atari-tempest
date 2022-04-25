//
// Created by massimo on 16/04/2022.
//

#ifndef TEMPEST_ATARI_TANKER_HPP
#define TEMPEST_ATARI_TANKER_HPP

#include "GameObject.hpp"
class Tanker : public GameObject
{
private:
  bool split_ = false;

public:
  Tanker();
  //  explicit Tanker(u8 band_num);
  Tanker(const Tanker& tanker) = default;
  ~Tanker() override = default;

  //  void activate(const Map& map, u8 band_num);
  void render(SDLW::Renderer& renderer,
              const Map& map,
              const color& render_color) const override;
  void update(f64 delta, const Map& map) override;
  inline bool isSplit() const { return split_; }
  inline void setSplit(bool split) { split_ = split; }
};

#endif // TEMPEST_ATARI_TANKER_HPP
