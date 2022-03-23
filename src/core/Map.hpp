/**
 * @file Map.hpp
 * @author massimo
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef TEMPEST_ATARI_MAP_HPP
#define TEMPEST_ATARI_MAP_HPP

#include "Band.hpp"
#include <vector>
class Map
{
private:
  std::vector<Band> bands_;
  bool is_continuous_{ false };
  u8 selected_band_num_{ 0 };
  void setBands(const std::vector<Vector2D>& exterior,
                const std::vector<Vector2D>& interior);

public:
  Map() = default;
  Map(const Map& map) = default;
  Map(const std::vector<Vector2D>& exterior,
      const std::vector<Vector2D>& interior,
      bool is_continuous);
  u8 getLeftBandNum(u8 num_band) const;
  u8 getRightBandNum(u8 num_band) const;
  const Band& getBand(u8 num_band) const;
  const Band& getLeftBand(u8 num_band) const;
  const Band& getRightBand(u8 num_band) const;
  Vector2D calcPosition(u8 num_band, f32 progress) const;
  void render(SDL_Renderer* renderer) const;
  void select(u8 num_band);
  void reset(const std::vector<Vector2D>& exterior,
             const std::vector<Vector2D>& interior,
             bool is_continuous);
  ~Map() = default;
};

#endif // TEMPEST_ATARI_MAP_HPP
