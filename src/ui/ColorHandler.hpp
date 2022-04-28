/**
 * @file ColorHandler.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "../utils/types.hpp"
#include <array>
#include <string>
#include <vector>

class ColorHandler
{
private:
  inline static const std::string COLOR_DATA_PATH_ = "data/color_data.txt";
  std::vector<color> colors_;
  std::array<std::array<i32, 5>, 7> color_indices_;

public:
  ColorHandler();
  ~ColorHandler();

  const color& get_map_standard_colors(i32 cycle) const;
  const color& get_map_selected_colors(i32 cycle) const;
  const color& get_blaster_colors(i32 cycle) const;
  const color& get_flipper_colors(i32 cycle) const;
  const color& get_tanker_colors(i32 cycle) const;
  const color& get_spiker_colors(i32 cycle) const;
  const color& get_score_colors(i32 cycle) const;
};
