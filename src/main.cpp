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
#include "types.h"

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

int
main(void)
{
  cout << "Main.cpp correctly launched" << endl;
  GameObject g = GameObject();

  while (g.run != 0) {
    g.trun();
    g.stop();
  }

  g.~GameObject();
  return 0;
}
