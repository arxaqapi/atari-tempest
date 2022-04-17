/**
 * @file Utils.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-02-02
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef H_TEMPEST_GAME_INC_ERRORS_
#define H_TEMPEST_GAME_INC_ERRORS_

#include "types.hpp"
#include <stdexcept>

namespace errors {
struct not_implemented : public std::exception
{
  const char* what() const throw();
};
struct not_tested : public std::exception
{
  const char* what() const throw();
};

struct non_valid_state_switch : public std::exception
{
  const char* what() const throw();
};

struct file_not_opened : public std::exception
{
  const char* what() const throw();
};

struct non_valid_character_requested : public std::exception
{
  const char* what() const throw();
};

inline f32
easeOutQuad(f32 x, f32 frac)
{
  return 1 - frac * (1 - x) * (1 - x);
}
}

#endif