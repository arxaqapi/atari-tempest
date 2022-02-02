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
#include <cassert>
#include <iostream>

Timer::Timer(u32 max_ms_per_frame)
  : t_(NORMAL)
  , max_ms_per_frame_(max_ms_per_frame)
  , distribution_{ 0, static_cast<int>(max_ms_per_frame) - 4 }
  , start_{ 0 }
  , stop_{ 0 }
  , fps_{ 0.0 }
{}

Timer::Timer(u32 max_ms_per_frame, timer_type t)
  : t_(t)
  , max_ms_per_frame_(max_ms_per_frame)
  , distribution_{ 0, static_cast<int>(max_ms_per_frame) - 4 }
  , start_{ 0 }
  , stop_{ 0 }
  , fps_{ 0.0 }
{}

Timer::~Timer() {}

void
Timer::start()
{
  if (t_ == NORMAL) {
    start_ = SDL_GetTicks();
  } else if (t_ == PERFORMANCE) {
    start_ = SDL_GetPerformanceCounter();
  }
}

double
to_ms(double value)
{
  auto freq_in_ms = static_cast<double>(SDL_GetPerformanceFrequency()) / 1000.;
  return value / freq_in_ms;
}

double
Timer::stop()
{
  if (t_ == NORMAL) {
    stop_ = SDL_GetTicks();
    return stop_ - start_;
  } else if (t_ == PERFORMANCE) {
    stop_ = SDL_GetPerformanceCounter();
    return to_ms(stop_ - start_);
  }
  return 0.;
}

double
Timer::get_FPS()
{
  if (t_ == NORMAL) {
    return 1. / ((stop_ - start_) / 1000.);
  } else if (t_ == PERFORMANCE) {
    return 1. / ((to_ms(stop_ - start_) / 1000.));
  }
  return 0.;
}

void
Timer::print()
{
  std::cout << "[Log] - FPS = " << get_FPS() << std::endl;
}

void
Timer::variable_delay()
{
  u64 ms_elapsed;
  if (t_ == NORMAL) {
    ms_elapsed = stop_ - start_;
  } else if (t_ == PERFORMANCE) {
    ms_elapsed = to_ms(stop_ - start_);
  } else {
    throw utils::not_implemented();
  }
  auto del = max_ms_per_frame_ - ms_elapsed;
  assert(del <= max_ms_per_frame_ && "Computed delay is way too big");
  SDL_Delay(del);
  this->stop();
}

void
Timer::artificial_delay()
{
  auto r = static_cast<u32>(distribution_(generator_));
  assert(r < max_ms_per_frame_ && r >= 0);
  SDL_Delay(r);
}
