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

using namespace std;

int
main(void)
{
  cout << "Main.cpp correctly launched" << endl;
  GameObject g;
  Timer timer;

  // 1 / (24 / 1000) = {42} || 1000 / {41} = 24.3
  const u32 max_ms_per_frame = 1000.f / 30.f;

  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, max_ms_per_frame - 4);

  g.init();
  while (g.is_running()) {
    Uint32 start = SDL_GetTicks();
    //// SECTION: Loop start
    g.process_events();
    g.clear();
    g.update_state(0);
    g.render();
    SDL_Delay(distribution(generator)); // artificial delay
    //// !SECTION: Loop end
    timer.get_FPS();

    Uint32 end = SDL_GetTicks();
    float ms_elapsed = (end - start);

    SDL_Delay(max_ms_per_frame - ms_elapsed); // delay for exactly 1000 / 30 ms
    end = SDL_GetTicks();
    cout << "FPS: " << 1. / ((end - start) / 1000.)
         << endl; // fréquence du temps passé en secondes
  }
  return 0;
}
