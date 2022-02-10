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

#ifndef H_TEMPEST_GAME_INC_UTILS_
#define H_TEMPEST_GAME_INC_UTILS_

#include <stdexcept>

namespace utils {
struct not_implemented : public std::exception
{
  const char* what() const throw();
};
struct not_tested : public std::exception
{
  const char* what() const throw();
};
}

#endif