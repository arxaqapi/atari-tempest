/**
 * @file GameObject.hpp
 * @author massimo
 * @version 0.1
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2022
 */

#ifndef TEMPEST_ATARI_GAMEOBJECT_HPP
#define TEMPEST_ATARI_GAMEOBJECT_HPP

#include "../sdlw/SDLW.hpp"
#include "../utils/Delay.hpp"
#include "../utils/Utils.hpp"
#include "../utils/types.hpp"
#include "Map.hpp"

/**
 * @brief Énumération des directions possibles pour le déplacement de l'objet
 */
enum e_direction
{
  NONE,
  LEFT,
  RIGHT,
  FORWARD,
  BACKWARD
};

class GameObject
{
protected:
  u8 band_num_ = 0;
  /**
   * @brief Booléen indiquant si l'objet est actif ou non. Utile pour gérer une
   * pool d'objets.
   */
  bool active_ = true;
  f32 front_progression_ = 0;
  f32 lateral_progression_ = 0;
  f32 front_velocity_ = 0.0005;
  f32 lateral_velocity_ = 0.02;
  enum e_direction moving_direction_ = NONE;

  /**
   * @brief Déplace le joueur
   * @param delta Temps passé depuis le dernnier appel
   * @param map Carte
   */
  void move(f64 delta, const Map& map);

public:
  GameObject() = default;
  GameObject(const GameObject& go) = default;
  virtual ~GameObject() = default;

  /**
   * @brief Active l'objet et l'initialise
   * @param band_num Numéro de bande sur laquelle est l'objet
   * @param front_progression Progression de l'objet le long de la bande
   * @param lateral_progression Progression latérale de l'objet
   * @param front_velocity Vitesse le long de la bande
   * @param lateral_velocity Vitesse latérale
   * @param moving_direction Direction
   */
  void activate(u8 band_num,
                f32 front_progression,
                f32 lateral_progression,
                f32 front_velocity,
                f32 lateral_velocity,
                e_direction moving_direction);

  /**
   * @brief Teste si l'objet est en collision avec un autre objet
   * @param go L'objet avec qui la collision est testée
   * @return Vrai si il y a collision, faux sinon
   */
  bool isColliding(const GameObject& go) const;

  /**
   * @brief Action à réaliser lorsque l'objet est rentré en collision avec un
   * autre. Désactive l'objet par défaut
   */
  inline virtual void hit() { deactivate(); }

  /**
   * @brief Appelée à chaque pas de temps pour mettre à jour l'objet
   * @param delta Temps passé depuis le dernier appel
   * @param map Carte du niveau courant
   */
  virtual void update(f64 delta, const Map& map) = 0;

  /**
   * @brief Réalise le rendu de l'objet
   * @param renderer Wrapper du renderer SDL
   * @param map Carte du niveau courant
   * @param render_color Couleur de l'objet
   */
  virtual void render(SDLW::Renderer& renderer,
                      const Map& map,
                      const color& render_color) const = 0;

  /**
   * Getters
   */
  inline bool isActive() const { return active_; }
  inline u8 getBandNum() const { return band_num_; }
  inline f32 getFrontProgression() const { return front_progression_; }

  /**
   * Setters
   */
  void setMovingDirection(e_direction moving_direction)
  {
    moving_direction_ = moving_direction;
  }
  inline void deactivate() { active_ = false; }
};

#endif // TEMPEST_ATARI_GAMEOBJECT_HPP
