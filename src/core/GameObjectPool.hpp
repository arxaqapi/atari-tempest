//
// Created by massimo on 24/03/2022.
//

#ifndef TEMPEST_ATARI_GAMEOBJECTPOOL_HPP
#define TEMPEST_ATARI_GAMEOBJECTPOOL_HPP

#include "../utils/Timer.hpp"
#include "../utils/types.hpp"
#include "Map.hpp"
#include <iostream>

template<typename GameObjectType>
class GameObjectPool
{
private:
  //  f32 spawn_delay_, last_spawns_delay_;
  u8 pool_size_{ 0 }, available_objects_{ 0 };
  std::vector<GameObjectType> pool_;
  int find();

public:
  GameObjectPool() = default;
  explicit GameObjectPool(u8 pool_size);
  GameObjectPool(const GameObjectPool& go_pool) = default;
  ~GameObjectPool() = default;

  void create(u8 band_num);
  void update(const Map& map);
  void render(SDL_Renderer* renderer, const Map& map) const;
};

template<typename GameObjectType>
GameObjectPool<GameObjectType>::GameObjectPool(u8 pool_size)
  : pool_size_{ pool_size }
  , available_objects_{ pool_size }
  , pool_(pool_size)
{}

template<typename GameObjectType>
int
GameObjectPool<GameObjectType>::find()
{
  if (available_objects_ == 0)
    return -1;

  u8 index = 0;
  for (index = 0; index < pool_size_ && pool_[index].isActive(); ++index)
    ;
  return index < pool_size_ ? index : -1;
}

template<typename GameObjectType>
void
GameObjectPool<GameObjectType>::create(u8 band_num)
{
  int index = find();
  if (index == -1)
    return;
  pool_[index].activate(band_num);
  available_objects_--;
}

template<typename GameObjectType>
void
GameObjectPool<GameObjectType>::update(const Map& map)
{
  for (auto& go : pool_)
    go.update(map);
}

template<typename GameObjectType>
void
GameObjectPool<GameObjectType>::render(SDL_Renderer* renderer,
                                       const Map& map) const
{
  for (auto& go : pool_)
    go.render(renderer, map);
}

#endif // TEMPEST_ATARI_GAMEOBJECTPOOL_HPP
