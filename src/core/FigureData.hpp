//
// Created by massimo on 13/04/2022.
//

#ifndef TEMPEST_ATARI_FIGUREDATA_HPP
#define TEMPEST_ATARI_FIGUREDATA_HPP

#include "../utils/Vector2D.hpp"
#include "../utils/types.hpp"
#include <string>
#include <vector>
class FigureData
{
private:
  Vector2D origin;
  std::vector<Vector2D> exterior_;
  f32 focal_ = 0;
  bool is_continuous_ = false;
  u8 figure_num_ = 0;

public:
  inline static const std::string FIGURES_DATA_DIR_ = "data/";
  inline static const std::string FIGURE_PREFIX_ = "figure-";

  FigureData() = default;
  FigureData(const FigureData& data) = default;
  explicit FigureData(u8 level);
  ~FigureData() = default;

  const Vector2D& getOrigin() const;
  f32 getFocal() const;
  const std::vector<Vector2D>& getExterior() const;
  bool isContinuous() const;
  i8 getFigureNum() const;
  bool load(u8 figure);
};

#endif // TEMPEST_ATARI_FIGUREDATA_HPP
