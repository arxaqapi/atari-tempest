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

#include "GameObject.hpp"
#include "Timer.hpp"

#include "types.hpp"
#include <iostream>
#include <random>

int
main(void)
{
  std::cout << "Main.cpp correctly launched" << std::endl;
  GameObject g;
  Timer timer;

  // 1 / (24 / 1000) = {42} || 1000 / {41} = 24.3
  const u32 max_ms_per_frame = 1000.f / 30.f;

  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, max_ms_per_frame - 4);

  g.init();
  while (g.is_running()) {
    timer.start();
    //// SECTION: Loop start

    g.process_events();
    g.clear();
    g.update_state(0);
    g.render();
    // auto r = distribution(generator);
    // SDL_Delay(r); // artificial delay

    //// !SECTION: Loop end
    timer.stop();
    timer.variable_delay(max_ms_per_frame);
    timer.print();
  }
  return 0;
}
