/**
 * @file SpawnManager.hpp
 * @author massimo
 * @version 0.1
 * @date 2022-03-24
 *
 * @copyright Copyright (c) 2022
 */

#ifndef TEMPEST_ATARI_SPAWNMANAGER_HPP
#define TEMPEST_ATARI_SPAWNMANAGER_HPP

#include "../sdlw/SDLW.hpp"
#include "../utils/types.hpp"
#include "Flipper.hpp"
#include "GameObjectPool.hpp"
#include "Spiker.hpp"
#include "Tanker.hpp"

/**
 * @brief Gère le spawn des ennemis
 */
class SpawnManager
{
private:
  static const u8 MAX_TANKERS_ = 4;
  static const u8 MAX_FLIPPERS_ = 15;
  static const u8 MAX_SPIKERS_ = 4;
  static constexpr f64 SPAWN_DELAY_ = 2000;
  Delay spawn_delay_{ SPAWN_DELAY_ };
  std::random_device rd;
  std::default_random_engine generator_{ rd() };
  std::uniform_int_distribution<u8> spawn_type_distribution_{ 0, 1 };
  std::uniform_int_distribution<u8> band_num_distribution_{ 0, 0 };
  /**
   * Les pools d'ennemis
   */
  GameObjectPool<Flipper> flippers_{ MAX_FLIPPERS_ };
  GameObjectPool<Tanker> tankers_{ MAX_TANKERS_ };
  GameObjectPool<Spiker> spikers_{ MAX_SPIKERS_ };

  /**
   * @brief Fixe les bornes du générateur de nombres aléatoires pour le type
   * d'ennemi à spawn en fonction du niveau
   * @param level Niveau pour lequel il faut fixer les bornes du générateur
   */
  void setSpawnTypeDistribution(u8 level);

public:
  SpawnManager() = default;
  SpawnManager(const SpawnManager& spawn_manager) = default;
  SpawnManager(u8 max_band_num, u8 level);

  /**
   * @brief Fait apparaître un nouvel ennemi si le temps écoulé depuis le
   * dernier appel est suffisamment important. Le type d'ennemi est choisi
   * aléatoirement. Si la pool du type d'ennemi choisi est pleine, ie tous les
   * objets de la pool sont actifs, alors rien ne se passe
   * @param delta Temps écoulé depuis le dernier appel
   * @param level Niveau actuel, influe sur les ennemis qui peuvent être créés
   */
  void spawn(f64 delta, u8 level);

  /**
   * @brief Fait apparaître un Flipper. Si la pool de Flippers est pleine, ie
   * tous les Flippers de la pool sont actifs, alors rien ne se passe
   * @param band_num Bande sur laquelle faire apparaître le Flipper
   * @param front_progression Progression du Flipper le long de la bande
   * @param level Niveau actuel, influe sur la possibilité de changer de bande
   * du Flipper
   * @return Itérateur pointant sur le Flipper créé dans la pool de Flippers ou
   * `flippers.end()` si la pool est déjà pleine
   */
  std::vector<Flipper>::iterator spawnFlipper(u8 band_num,
                                              f32 front_progression,
                                              u8 level);

  /**
   * @brief Fait apparaître un Flipper. Si la pool de Flippers est pleine, ie
   * tous les Flippers de la pool sont actifs, alors rien ne se passe
   * @param band_num Bande sur laquelle faire apparaître le Flipper
   * @param front_progression Progression du Flipper le long de la bande
   * @param level Niveau actuel, influe sur la possibilité de changer de bande
   * du Flipper
   * @param band_change_direction Direction du Flipper pour le changement de
   * bande
   * @return Itérateur pointant sur le Flipper créé dans la pool de Flippers ou
   * `flippers.end()` si la pool est déjà pleine
   */
  std::vector<Flipper>::iterator spawnFlipper(
    u8 band_num,
    f32 front_progression,
    u8 level,
    e_direction band_change_direction);

  /**
   * @brief Appelée à chaque pas de temps pour mettre à jour et spawn les
   * ennemis. Appelle la fonction `update` sur chaque ennemi
   * @param delta Temps passé depuis le dernier appel
   * @param map Carte du niveau courant
   * @param level Niveau courant
   */
  void update(f64 delta, const Map& map, u8 level);

  /**
   * @brief Réalise le rendu des ennemis. Appelle la fonction `render` sur
   * chaque ennemi
   * @param renderer Wrapper du renderer SDL
   * @param map Carte du niveau courant
   * @param flipper_color Couleur pour le rendu des Flippers
   * @param tanker_color Couleur pour le rendu des Tankers
   * @param spiker_color Couleur pour le rendu des Spikers
   */
  void render(SDLW::Renderer& renderer,
              const Map& map,
              const color& flipper_color,
              const color& tanker_color,
              const color& spiker_color) const;

  /**
   * @brief Réinitialise l'objet. Réinitialise les pools d'ennemis et le délai
   * de spawn
   */
  void clear();

  /**
   * @brief Initialise le manager. Les anciennes valeurs des membres de la
   * classe sont écrasées.
   * @param max_band_num Numéro de bande maximal sur laquelle les ennemis
   * peuvent être créés
   * @param level Niveau courant, influe sur les ennemis qui peuvent être créés
   */
  void load(u8 max_band_num, u8 level);

  /**
   * Getters
   */
  inline std::vector<Flipper>& getFlippers() { return flippers_.getPool(); };
  inline std::vector<Tanker>& getTankers() { return tankers_.getPool(); };
  inline std::vector<Spiker>& getSpikers() { return spikers_.getPool(); };
};

#endif // TEMPEST_ATARI_SPAWNMANAGER_HPP
