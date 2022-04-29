/**
 * @file types.hpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
 * @brief
 * @version 0.1
 * @date 2022-01-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef H_TEMPEST_GAME_INC_TYPES_
#define H_TEMPEST_GAME_INC_TYPES_

#include <cstdint>
#include <tuple>

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

using color = std::tuple<u8, u8, u8>;

#endif
