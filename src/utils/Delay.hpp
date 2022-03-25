//
// Created by massimo on 25/03/2022.
//

#ifndef TEMPEST_ATARI_DELAY_HPP
#define TEMPEST_ATARI_DELAY_HPP

#include "types.hpp"
class Delay
{
private:
  f64 min_delay_{0}, current_delay_{min_delay_};

public:
  Delay() = default;
  Delay(const Delay &delay) = default;
  explicit Delay(f64 min_delay) : min_delay_{min_delay} {}
  ~Delay() = default;

  inline void set(f64 min_delay) {
    min_delay_ = min_delay;
  }
  inline void reset() {
    current_delay_ = 0;
  }
  inline bool complete() const {
    return current_delay_ > min_delay_;
  }
  inline void update(f64 delta) {
    current_delay_ += delta;
  }

};

#endif // TEMPEST_ATARI_DELAY_HPP
