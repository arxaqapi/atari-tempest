/**
 * @file SpawnManager.cpp
 * @author massimo
 * @version 0.1
 * @date 2022-03-24
 *
 * @copyright Copyright (c) 2022
 */

#include "SpawnManager.hpp"

SpawnManager::SpawnManager(u8 max_band_num, u8 level)
  : band_num_distribution_{ 0, static_cast<u8>(max_band_num - 1) }
{
  setSpawnTypeDistribution(level);
}

void
SpawnManager::update(f64 delta, const Map& map, u8 level)
{
  spawn(delta, level);

  flippers_.update(delta, map);
  spikers_.update(delta, map);

  for (auto& tanker : tankers_.getPool()) {
    tanker.update(delta, map);
    if (tanker.isSplit()) {
      spawnFlipper(map.getLeftBandNum(tanker.getBandNum()),
                   tanker.getFrontProgression(),
                   level,
                   LEFT);
      spawnFlipper(map.getRightBandNum(tanker.getBandNum()),
                   tanker.getFrontProgression(),
                   level,
                   RIGHT);
      tanker.setSplit(false);
    }
  }
}

void
SpawnManager::render(SDLW::Renderer& renderer,
                     const Map& map,
                     const color& flipper_color,
                     const color& tanker_color,
                     const color& spiker_color) const
{
  flippers_.render(renderer, map, flipper_color);
  tankers_.render(renderer, map, tanker_color);
  spikers_.render(renderer, map, spiker_color);
}

void
SpawnManager::clear()
{
  flippers_.clear();
  spikers_.clear();
  tankers_.clear();
  spawn_delay_.reset();
}

std::vector<Flipper>::iterator
SpawnManager::spawnFlipper(u8 band_num, f32 front_progression, u8 level)
{
  if (level > 0)
    return flippers_.create(
      band_num, front_progression, 0.5, 0.0005, 0.0015, FORWARD);
  return flippers_.create(band_num, front_progression, 0.5, 0.0005, 0, FORWARD);
}

std::vector<Flipper>::iterator
SpawnManager::spawnFlipper(u8 band_num,
                           f32 front_progression,
                           u8 level,
                           e_direction band_change_direction)
{
  auto it = spawnFlipper(band_num, front_progression, level);
  if (it != flippers_.getPool().end())
    (*it).setBandChangeDirection(band_change_direction);
  return it;
}

void
SpawnManager::load(u8 max_band_num, u8 level)
{
  clear();
  band_num_distribution_.reset();
  band_num_distribution_.param(
    std::uniform_int_distribution<u8>::param_type(0, max_band_num - 1));
  setSpawnTypeDistribution(level);
}

void
SpawnManager::spawn(f64 delta, u8 level)
{
  spawn_delay_.update(delta);

  if (!spawn_delay_.complete())
    return;

  spawn_delay_.reset();

  u8 band_num = band_num_distribution_(generator_);
  u8 spawn_type = spawn_type_distribution_(generator_);

  switch (spawn_type) {
    case 0:
      spawnFlipper(band_num, 1, level);
      break;
    case 1:
      tankers_.create(band_num, 1, 0.5, 0.0001, 0, FORWARD);
      break;
    case 2:
      spikers_.create(band_num, 1, 0.5, 0.00005, 0, FORWARD);
      break;
  }
}

void
SpawnManager::setSpawnTypeDistribution(u8 level)
{
  spawn_type_distribution_.reset();
  if (level >= 4)
    spawn_type_distribution_.param(
      std::uniform_int_distribution<u8>::param_type(0, 2));
  else if (level >= 2)
    spawn_type_distribution_.param(
      std::uniform_int_distribution<u8>::param_type(0, 1));
  else
    spawn_type_distribution_.param(
      std::uniform_int_distribution<u8>::param_type(0, 0));
}
