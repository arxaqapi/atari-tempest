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

#include "../utils/Vector2D.hpp"
#include "../utils/types.hpp"
#include <SDL2/SDL_render.h>
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
  Band(Vector2D exter_a, Vector2D exter_b, Vector2D inter_a, Vector2D inter_b);
  ~Band() = default;

  Vector2D calcPosition(f32 progress) const;
  Vector2D calcPosition(Vector2D vec) const;
  void render(SDL_Renderer* renderer) const;
  inline void select() { is_selected_ = true; };
  inline void unselect() { is_selected_ = false; };
  inline f32 getDepth() const { return depth_; };
  inline std::pair<Vector2D, Vector2D> getExterior() const
  {
    return { exter_a_, exter_b_ };
  };
  inline std::pair<Vector2D, Vector2D> getInterior() const
  {
    return { inter_a_, inter_b_ };
  };
};

#endif // TEMPEST_ATARI_BAND_HPP
