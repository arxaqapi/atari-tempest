//
// Created by massimo on 24/03/2022.
//

#ifndef TEMPEST_ATARI_GAMEOBJECTPOOL_HPP
#define TEMPEST_ATARI_GAMEOBJECTPOOL_HPP

#include "../utils/Timer.hpp"
#include "../utils/types.hpp"
#include "Map.hpp"
#include <cassert>
#include <iostream>

template<typename GameObjectType>
class GameObjectPool
{
private:
  u8 pool_size_{ 0 };
  std::vector<GameObjectType> pool_;
  typename std::vector<GameObjectType>::iterator find();

public:
  GameObjectPool() = default;
  explicit GameObjectPool(u8 pool_size);
  GameObjectPool(const GameObjectPool& go_pool) = default;
  ~GameObjectPool() = default;

  GameObjectType& get(u8 i);
  std::vector<GameObjectType>& getPool();
  typename std::vector<GameObjectType>::iterator create(
    u8 band_num,
    f32 front_progression,
    f32 lateral_progression,
    f32 front_velocity,
    f32 lateral_velocity,
    e_direction moving_direction);
  void update(f64 delta, const Map& map);
  void render(SDL_Renderer* renderer, const Map& map) const;
  void clear();
};

template<typename GameObjectType>
GameObjectPool<GameObjectType>::GameObjectPool(u8 pool_size)
  : pool_size_{ pool_size }
  , pool_(pool_size)
{}

template<typename GameObjectType>
typename std::vector<GameObjectType>::iterator
GameObjectPool<GameObjectType>::find()
{
  return std::find_if(
    pool_.begin(), pool_.end(), [](GameObjectType go) { return !go.isActive(); });
}

template<typename GameObjectType>
typename std::vector<GameObjectType>::iterator
GameObjectPool<GameObjectType>::create(u8 band_num,
                                       f32 front_progression,
                                       f32 lateral_progression,
                                       f32 front_velocity,
                                       f32 lateral_velocity,
                                       e_direction moving_direction)
{
  auto it = find();
  if (it != pool_.end())
    (*it).activate(band_num,
                   front_progression,
                   lateral_progression,
                   front_velocity,
                   lateral_velocity,
                   moving_direction);
  return it;
}

template<typename GameObjectType>
void
GameObjectPool<GameObjectType>::update(f64 delta, const Map& map)
{
  for (auto& go : pool_)
    go.update(delta, map);
}

template<typename GameObjectType>
void
GameObjectPool<GameObjectType>::render(SDL_Renderer* renderer,
                                       const Map& map) const
{
  for (auto& go : pool_)
    go.render(renderer, map);
}

template<typename GameObjectType>
std::vector<GameObjectType>&
GameObjectPool<GameObjectType>::getPool()
{
  return pool_;
}

template<typename GameObjectType>
void
GameObjectPool<GameObjectType>::clear()
{
  std::for_each(pool_.begin(), pool_.end(), [](GameObjectType &go) { go.deactivate(); });
}

template<typename GameObjectType>
GameObjectType&
GameObjectPool<GameObjectType>::get(u8 i)
{
  assert(i < pool_size_ && i >= 0);
  return pool_[i];
}

#endif // TEMPEST_ATARI_GAMEOBJECTPOOL_HPP
