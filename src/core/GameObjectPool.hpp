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
  u8 pool_size_{ 0 };
  std::vector<GameObjectType> pool_;
  int find();

public:
  GameObjectPool() = default;
  explicit GameObjectPool(u8 pool_size);
  GameObjectPool(const GameObjectPool& go_pool) = default;
  ~GameObjectPool() = default;

  std::vector<GameObjectType>& getPool();
  void create(const Map& map, u8 band_num);
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
int
GameObjectPool<GameObjectType>::find()
{
  u8 index = 0;
  for (index = 0; index < pool_size_ && pool_[index].isActive(); ++index)
    ;
  return index < pool_size_ ? index : -1;
}

template<typename GameObjectType>
void
GameObjectPool<GameObjectType>::create(const Map& map, u8 band_num)
{
  int index = find();
  if (index == -1)
    return;
  pool_[index].activate(map, band_num);
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
  for (int i = 0; i < pool_size_; ++i) {
    pool_[i].deactivate();
  }
}

#endif // TEMPEST_ATARI_GAMEOBJECTPOOL_HPP
