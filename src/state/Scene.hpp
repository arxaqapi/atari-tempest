/**
 * @file Scene.cpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-02-10
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */
#ifndef H_TEMPEST_GAME_INC_SCENE_
#define H_TEMPEST_GAME_INC_SCENE_

#include "../sdlw/SDLW.hpp"
#include "../utils/types.hpp"
#include <SDL2/SDL.h>
#include <vector>

class SceneManager;

/**
 * \~french @brief Classe abstraite définissant la structure de base d'une scène
 * du jeu
 *
 */
class Scene
{
private:
public:
  Scene() = default;
  Scene(const Scene& scene) = default;
  ~Scene() = default;

  /**
   * \~french @brief Fonction purement virtuelle permettant la gestion des
   * évènemment spécifique à la scène
   *
   * \~french @param event Pointeur sur la structure de l'évènement // TODO: to
   * wrap
   * \~french @param sm référence sur le gestionnaire de scène, permettant de
   * demander un changement d'état
   */
  virtual void processEvent(const SDLW::Event& event, SceneManager& sm) = 0;
  /**
   * \~french @brief Fonction purement virtuelle permettant la mise à jour de
   * l'état interne de la scène
   *
   * \~french @param delta le temps delta issue du timer
   * \~french @param sm référence sur le gestionnaire de scène, permettant de
   * demander et d'acter un changement d'état
   */
  virtual void update(f64 delta, SceneManager& sm) = 0;
  /**
   * \~french @brief Fonction purement virtuelle permettant de rendre les
   * différents éléments de la scène sur l'objet Renderer
   *
   * \~french @param renderer Référence sur le Renderer courant
   */
  virtual void render(SDLW::Renderer& renderer) const = 0;
};

#endif