//
// Created by massimo on 16/03/2022.
//

#ifndef TEMPEST_ATARI_DATA_HPP
#define TEMPEST_ATARI_DATA_HPP

#include "../utils/Vector2D.hpp"
#include <string>
#include <vector>
class Data
{
private:
  inline static const std::string DATA_PATH_ = "data/level_data.txt";

  std::vector<std::vector<Vector2D>> exterior_;
  std::vector<Vector2D> origin_;
  std::vector<f32> focal_;
  std::vector<bool> is_continuous_;

  void readCoords(std::ifstream& file, std::vector<Vector2D>& coords, u8 n_coords);

public:
  inline static const u8 N_FIGURES_ = 16;
  inline static const u8 N_BANDS_PER_FIGURE_ = 16;
  inline static const u8 N_CYCLES_ = 5;
  inline static const u8 N_LEVELS_ = 80;

  Data();
  Data(const Data& data) = default;
  ~Data() = default;

  inline const std::vector<std::vector<Vector2D>>& getExterior() const
  {
    return exterior_;
  }
  inline const std::vector<Vector2D>& getOrigin() const { return origin_; }
  inline const std::vector<f32>& getFocal() const { return focal_; }
  inline const std::vector<bool>& getIsContinuous() const
  {
    return is_continuous_;
  }
};

#endif // TEMPEST_ATARI_DATA_HPP
