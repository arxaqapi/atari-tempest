/**
 * @file main.cpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-01-27
 *
 * @copyright Copyright (c) 2022
 *
 * @brief Entry point of the program
 */

#include "core/Game.hpp"
#include "utils/Timer.hpp"
#include "utils/types.hpp"

#include <iostream>
#include <random>

int
main(void)
{
  std::cout << "Main.cpp correctly launched" << std::endl;

  constexpr u32 max_ms_per_frame = 1000.f / 30.f;
  f64 delta = 0;
  f64 ifd;
  Game g{ 763, 823 };
  Timer<timer_type::PERFORMANCE> timer{ max_ms_per_frame };

  while (g.is_running()) {
    timer.start();

    g.process_events();
    g.clear();
    g.update(delta);
    g.render();

    ifd = timer.stop();
    delta = timer.variable_delay();

    // Debug
    g.debug_set_fps(timer.get_FPS());
    g.debug_set_interframe_delay(ifd);
  }
  return 0;
}
