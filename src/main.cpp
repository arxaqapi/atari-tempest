/**
 * @file main.cpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
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
  Timer<TimerType::PERFORMANCE> timer{ max_ms_per_frame };

  while (g.isRunning()) {
    timer.start();

    g.processEvents();
    g.clear();
    g.update(delta);
    g.render();

    ifd = timer.stop();
    delta = timer.variableDelay();

    // Debug
    g.debugSetFPS(timer.getFPS());
    g.debugSetInterframeDelay(ifd);
  }
  return 0;
}
