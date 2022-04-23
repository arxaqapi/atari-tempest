//
// Created by massimo on 24/03/2022.
//

#ifndef TEMPEST_ATARI_SPAWNMANAGER_HPP
#define TEMPEST_ATARI_SPAWNMANAGER_HPP

#include "../utils/types.hpp"
#include "Flipper.hpp"
#include "GameObjectPool.hpp"
#include "Spiker.hpp"
#include "Tanker.hpp"

enum enemy_type
{
  FLIPPER,
  TANKER,
  SPIKER
};

class SpawnManager
{
private:
  static const u8 MAX_TANKERS_ = 4;
  static const u8 MAX_FLIPPERS_ = 15;
  static const u8 MAX_SPIKERS_ = 4;
  static constexpr f64 SPAWN_DELAY_ = 2000;

  GameObjectPool<Flipper> flippers_{ MAX_FLIPPERS_ };
  GameObjectPool<Tanker> tankers_{ MAX_TANKERS_ };
  GameObjectPool<Spiker> spikers_{ MAX_SPIKERS_ };

  Delay spawn_delay_{ SPAWN_DELAY_ };
  std::default_random_engine generator_;
  std::uniform_int_distribution<u8> spawn_distribution_;

public:
  SpawnManager() = default;
  SpawnManager(const SpawnManager& spawn_manager) = default;
  explicit SpawnManager(u8 max_band_num);

  std::vector<Flipper>& getFlippers();
  std::vector<Tanker>& getTankers();
  std::vector<Spiker>& getSpikers();

  int spawnFlipper(u8 band_num, f32 progress);
  int spawnFlipper(u8 band_num,
                   f32 progress,
                   e_direction band_change_direction);

  void update(f64 delta, const Map& map);
  void render(SDL_Renderer* renderer, const Map& map) const;
  void clear();
  void load(u8 max_band_num);
};

#endif // TEMPEST_ATARI_SPAWNMANAGER_HPP
