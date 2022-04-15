//
// Created by massimo on 13/04/2022.
//

#ifndef TEMPEST_ATARI_LEVELDATA_HPP
#define TEMPEST_ATARI_LEVELDATA_HPP

#include "../utils/Vector2D.hpp"
#include "../utils/types.hpp"
#include <string>
#include <vector>
class LevelData
{
private:
  inline static const std::string LEVELS_DATA_DIR_ = "data/";
  inline static const std::string LEVEL_PREFIX_ = "level-";
  Vector2D origin;
  std::vector<Vector2D> exterior_;
  f32 focal_;
  bool is_continuous_;
  u32 score_;
  u8 level_num_ = 0;
  static void parseCoordinates(const std::string& coordinates,
                               std::vector<Vector2D>& points);

public:
  LevelData() = default;
  LevelData(const LevelData& data) = default;
  explicit LevelData(u8 level);
  const Vector2D& getOrigin() const;
  f32 getFocal() const;
  ~LevelData() = default;
  const std::vector<Vector2D>& getExterior() const;
  bool isContinuous() const;
  u32 getScore() const;
  i8 getLevelNum() const;
  bool load(u8 level);
};

#endif // TEMPEST_ATARI_LEVELDATA_HPP
