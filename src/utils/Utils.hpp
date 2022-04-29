/**
 * @file Utils.hpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-02-02
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef H_TEMPEST_GAME_INC_UTILS_
#define H_TEMPEST_GAME_INC_UTILS_

#include "types.hpp"

namespace utils {
inline f32
easeOutQuad(f32 x, f32 frac)
{
  return 1 - frac * (1 - x) * (1 - x);
}
}

#endif