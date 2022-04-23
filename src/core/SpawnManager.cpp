//
// Created by massimo on 24/03/2022.
//

#include "SpawnManager.hpp"

SpawnManager::SpawnManager(u8 max_band_num)
  : spawn_distribution_{ 0, static_cast<u8>(max_band_num - 1) }
{}

void
SpawnManager::update(f64 delta, const Map& map)
{
  spawn_delay_.update(delta);
  if (spawn_delay_.complete()) {
    u8 band_num = spawn_distribution_(generator_);
    u8 spawn_type = spawn_distribution_(generator_) % 2;
    if (spawn_type == 0)
      tankers_.create(band_num, 1, 0.5, 0.0001, 0, FORWARD);
    else
      spikers_.create(band_num, 1, 0.5, 0.00005, 0, FORWARD);
    spawn_delay_.reset();
  }
  flippers_.update(delta, map);
  spikers_.update(delta, map);
  for (auto& tanker : tankers_.getPool()) {
    tanker.update(delta, map);
    if (tanker.isSplit()) {
      spawnFlipper(map.getLeftBandNum(tanker.getBandNum()),
                   tanker.getFrontProgression());
      spawnFlipper(map.getRightBandNum(tanker.getBandNum()),
                   tanker.getFrontProgression());
      tanker.setSplit(false);
    }
  }
}

void
SpawnManager::render(SDL_Renderer* renderer, const Map& map) const
{
  flippers_.render(renderer, map);
  tankers_.render(renderer, map);
  spikers_.render(renderer, map);
}

std::vector<Flipper>&
SpawnManager::getFlippers()
{
  return flippers_.getPool();
}

void
SpawnManager::clear()
{
  flippers_.clear();
  tankers_.clear();
  spikers_.clear();
  spawn_delay_.reset();
}

std::vector<Tanker>&
SpawnManager::getTankers()
{
  return tankers_.getPool();
}

std::vector<Spiker>&
SpawnManager::getSpikers()
{
  return spikers_.getPool();
}

int
SpawnManager::spawnFlipper(u8 band_num, f32 progress)
{
  return flippers_.create(band_num, progress, 0.5, 0.0005, 0.05, FORWARD);
}

int
SpawnManager::spawnFlipper(u8 band_num,
                           f32 progress,
                           e_direction band_change_direction)
{
  int index = spawnFlipper(band_num, progress);
  if (index != -1)
    flippers_.get(index).setBandChangeDirection(band_change_direction);
  return index;
}

void
SpawnManager::load(u8 max_band_num)
{
  clear();
  spawn_distribution_.param(std::uniform_int_distribution<u8>::param_type(0, max_band_num-1));
}
