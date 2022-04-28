//
// Created by massimo on 24/03/2022.
//

#ifndef TEMPEST_ATARI_GAMEOBJECTPOOL_HPP
#define TEMPEST_ATARI_GAMEOBJECTPOOL_HPP

#include "../sdlw/SDLW.hpp"
#include "../utils/Timer.hpp"
#include "../utils/types.hpp"
#include "Map.hpp"
#include <cassert>
#include <iostream>

/**
 * @brief Gère une pool d'objets
 * @tparam GameObjectType Type enfant de GameObject
 */
template<typename GameObjectType>
class GameObjectPool
{
private:
  std::vector<GameObjectType> pool_;

  /**
   * @brief Cherche le premier objet innactif de la pool
   * @return Itérateur pointant sur l'objet trouvé, peut pointer sur
   * `pool_.end()` si un tel objet n'a pas été trouvé
   */
  typename std::vector<GameObjectType>::iterator find();

public:
  GameObjectPool() = default;
  explicit GameObjectPool(u8 pool_size);
  GameObjectPool(const GameObjectPool& go_pool) = default;
  ~GameObjectPool() = default;

  /**
   * @brief Cherche le premier objet innactif de la pool. Si un tel objet est
   * trouvé, l'active et l'initialise.
   * Appelle la fonction `activate` deGameObject.
   * @return Itérateur pointant sur l'objet créé, peut pointer sur
   * `pool_.end()` si un tel objet n'a pas été trouvé
   */
  typename std::vector<GameObjectType>::iterator create(
    u8 band_num,
    f32 front_progression,
    f32 lateral_progression,
    f32 front_velocity,
    f32 lateral_velocity,
    e_direction moving_direction);

  /**
   * @brief Appelle la fonction `update` sur tous les objets de la pool
   */
  void update(f64 delta, const Map& map);

  /**
   * @brief Appelle la fonction `render` sur tous les objets de la pool
   */
  void render(SDLW::Renderer& renderer,
              const Map& map,
              const color& render_color) const;

  /**
   * @brief Réinitialise la pool d'objets (désactive tous les objets)
   */
  void clear();

  /**
   * Getters
   */
  inline std::vector<GameObjectType>& getPool() { return pool_; };
};

template<typename GameObjectType>
GameObjectPool<GameObjectType>::GameObjectPool(u8 pool_size)
  : pool_(pool_size)
{}

template<typename GameObjectType>
typename std::vector<GameObjectType>::iterator
GameObjectPool<GameObjectType>::find()
{
  return std::find_if(pool_.begin(), pool_.end(), [](GameObjectType go) {
    return !go.isActive();
  });
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
GameObjectPool<GameObjectType>::render(SDLW::Renderer& renderer,
                                       const Map& map,
                                       const color& render_color) const
{
  for (auto& go : pool_)
    go.render(renderer, map, render_color);
}

template<typename GameObjectType>
void
GameObjectPool<GameObjectType>::clear()
{
  for (auto& go : pool_)
    go.deactivate();
}

#endif // TEMPEST_ATARI_GAMEOBJECTPOOL_HPP
