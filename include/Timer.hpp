/**
 * @file Timer.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef H_TEMPEST_GAME_INC_TIMER_
#define H_TEMPEST_GAME_INC_TIMER_

#include "SDL2/SDL.h"
#include "Utils.hpp"
#include "types.hpp"
#include <random>

enum class timer_type
{
  NORMAL,
  PERFORMANCE
};

class Timer
{
private:
  timer_type t_;
  u32 max_ms_per_frame_;
  std::default_random_engine generator_;
  std::uniform_int_distribution<i32> distribution_;

  u64 start_;
  u64 stop_;
  f64 fps_;

public:
  /**
   * @brief Construct a new Timer object that will
   * count the number of milliseconds passed
   *
   */
  Timer(u32 max_ms_per_frame);
  Timer(u32 max_ms_per_frame, timer_type t);
  ~Timer();

  void start();
  /**
   * @brief Returns the time passed in ms between start() and stop()
   *
   * @return f64
   */
  f64 stop();

  f64 get_FPS();
  void print();
  /**
   * @brief resets the internal stop_ counter after the variable delay
   * has been applied, allows to get the exact delay between 2 frames
   * for FPS caping
   *
   */
  void variable_delay();
  /**
   * @brief Induces an artificial delay < max_ms_per_frame - 4
   * Mainly here to test clock mechanism like FPS caping
   *
   */
  void artificial_delay();
};

#endif