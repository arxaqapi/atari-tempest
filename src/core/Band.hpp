/**
 * @file Band.hpp
 * @author massimo
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef TEMPEST_ATARI_BAND_HPP
#define TEMPEST_ATARI_BAND_HPP

#include "../sdlw/SDLW.hpp"
#include "../utils/Vector2D.hpp"
#include "../utils/types.hpp"
#include <vector>

class Band
{
private:
  Vector2D exter_a_, exter_b_, inter_a_, inter_b_;
  Vector2D exter_center_, inter_center_;
  Vector2D axis_;
  Vector2D unit_vector_;
  f32 depth_{ 0 };
  bool is_selected_{ false };

public:
  const Vector2D& getExterCenter() const;

public:
  Band() = default;
  Band(const Band& band) = default;
  Band(Vector2D exter_a, Vector2D exter_b, Vector2D origin, f32 focal);
  ~Band() = default;

  void render(SDLW::Renderer& renderer,
              const color& standard_color,
              const color& accent_color) const;
  inline void select() { is_selected_ = true; };
  inline void unselect() { is_selected_ = false; };

  inline std::pair<Vector2D, Vector2D> getExterior() const
  {
    return { exter_a_, exter_b_ };
  };

  inline std::pair<Vector2D, Vector2D> getInterior() const
  {
    return { inter_a_, inter_b_ };
  }

  inline const Vector2D& getUnitVector() const { return unit_vector_; }
  inline const Vector2D& getAxis() const { return axis_; }
  inline const Vector2D& getInterCenter() const { return inter_center_; };
};

#endif // TEMPEST_ATARI_BAND_HPP
