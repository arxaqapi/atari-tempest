/**
 * @file Timer.cpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "Timer.hpp"
#include <iostream>

Timer::Timer()
  : fps_{ 0.0 }
  , start_{ 0 }
  , stop_{ 0 }
  , t_(NORMAL)
{}

Timer::Timer(timer_type t)
  : fps_{ 0.0 }
  , start_{ 0 }
  , stop_{ 0 }
  , t_(t)
{}

Timer::~Timer() {}

void
Timer::start()
{
  throw utils::not_tested();
  if (t_ == NORMAL) {
    start_ = SDL_GetTicks();
  } else if (t_ == PERFORMANCE) {
    start_ = SDL_GetPerformanceCounter();
  }
}

double
Timer::stop()
{
  throw utils::not_tested();
  if (t_ == NORMAL) {
    stop_ = SDL_GetTicks();
    return stop_ - start_;
  } else if (t_ == PERFORMANCE) {
    stop_ = SDL_GetPerformanceCounter();
    return (stop_ - start_) /
           static_cast<double>(SDL_GetPerformanceFrequency()) / 1000.;
  }
  return 0.;
}

double
Timer::get_FPS()
{
  throw utils::not_implemented();
  return 0.;
}

void
Timer::print()
{
  throw utils::not_implemented();
}
