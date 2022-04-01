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
  Game g{ 1000, 600 };
  Timer timer{ max_ms_per_frame, timer_type::PERFORMANCE };

  g.init();
  while (g.is_running()) {
    timer.start();
    //// SECTION: Loop start

    g.process_events();
    g.clear();
    g.update(delta);
    g.switch_scene();
    g.render();

    //    timer.artificial_delay();

    //// !SECTION: Loop end
    timer.stop();
    delta = timer.variable_delay();
    //    timer.print();
  }
  return 0;
}
