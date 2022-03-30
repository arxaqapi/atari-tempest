//
// Created by massimo on 24/03/2022.
//

#ifndef TEMPEST_ATARI_SPAWNMANAGER_HPP
#define TEMPEST_ATARI_SPAWNMANAGER_HPP

#include "../utils/types.hpp"
#include "Flipper.hpp"
#include "GameObjectPool.hpp"
class SpawnManager
{
private:
  static const u8 MAX_ENEMIES_ = 4;
  static constexpr f64 SPAWN_DELAY_ = 3000;
  GameObjectPool<Flipper> enemies_{ MAX_ENEMIES_ };
  Delay spawn_delay_{ SPAWN_DELAY_ };
  std::default_random_engine generator_;
  std::uniform_int_distribution<u8> spawn_distribution_;

public:
  SpawnManager() = default;
  SpawnManager(const SpawnManager& spawn_manager) = default;
  explicit SpawnManager(u8 max_band_num);

  void update(f64 delta, const Map& map);
  void render(SDL_Renderer* renderer, const Map& map) const;
};

#endif // TEMPEST_ATARI_SPAWNMANAGER_HPP
