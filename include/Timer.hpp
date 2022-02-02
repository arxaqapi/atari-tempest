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
#include "types.hpp"

#include "Utils.hpp"

enum timer_type
{
  NORMAL,
  PERFORMANCE
};

class Timer
{
private:
  double fps_;
  u64 start_;
  u64 stop_;
  timer_type t_;

public:
  /**
   * @brief Construct a new Timer object that will
   * count the number of milliseconds passed
   *
   */
  Timer();
  Timer(timer_type t);
  ~Timer();

  void start();
  /**
   * @brief Returns the time passed in ms between start() and stop()
   *
   * @return double
   */
  double stop();

  double get_FPS();
  void print();
  /**
   * @brief resets the internal stop_ counter after the variable delay
   * has been applied, allows to get the exact delay between 2 frames
   * for FPS caping 
   * 
   * @param max_ms_per_frame the maximum of allowed ms per frame 
   */
  void variable_delay(u32 max_ms_per_frame);
};

#endif