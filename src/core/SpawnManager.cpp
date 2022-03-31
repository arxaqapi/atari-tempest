//
// Created by massimo on 24/03/2022.
//

#include "SpawnManager.hpp"

SpawnManager::SpawnManager(u8 max_band_num)
  : spawn_distribution_{ 0, static_cast<u8>(max_band_num - 1) }
{}

void
SpawnManager::update(f64 delta, const Map &map)
{
  spawn_delay_.update(delta);
  if (spawn_delay_.complete()) {
    enemies_.create(spawn_distribution_(generator_));
    spawn_delay_.reset();
  }
  enemies_.update(delta, map);
}

void
SpawnManager::render(SDL_Renderer* renderer, const Map& map) const
{
  enemies_.render(renderer, map);
}

std::vector<Flipper>&
SpawnManager::getEnnemies()
{
  return enemies_.getPool();
}
