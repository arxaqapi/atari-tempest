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
  std::vector<std::vector<Vector2D>> exteriors_;
  std::vector<std::vector<Vector2D>> interiors_;
  std::vector<bool> is_continuous_;
  std::vector<u32> scores_;
  u8 n_levels_{ 0 };
  static void parseCoordinates(const std::string& coordinates,
                               std::vector<Vector2D>& points);
  void parseLine(const std::string& line);
  void loadData(const std::string& data_path);

public:
  Data() = default;
  Data(const Data& data) = default;
  explicit Data(std::string data_path);
  ~Data() = default;
  const std::vector<Vector2D>& getExterior(u8 i) const;
  const std::vector<Vector2D>& getInterior(u8 i) const;
  bool isContinuous(u8 i) const;
  u32 getScore(u8 i) const;
  u8 getNLevels() const;
};

#endif // TEMPEST_ATARI_DATA_HPP
