/**
 * @file WinScreen.hpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-13
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef H_TEMPEST_GAME_WINSCREEN_TITLESCREEN_
#define H_TEMPEST_GAME_WINSCREEN_TITLESCREEN_

#include "Scene.hpp"

class SceneManager;

/**
 * @brief Classe définissant la logique propre à la scène invoquée lors de la
 * victoire du joueur
 *
 */
class WinScreen : public Scene
{
private:
public:
  WinScreen();
  ~WinScreen();

  /**
   * @brief Fonction permettant la gestion des évènemment spécifique à la scène
   *
   * @param event Pointeur sur la structure de l'évènement
   * @param sm référence sur le gestionnaire de scène, permettant de
   * demander un changement d'état
   */
  void processEvent(const SDLW::Event& event, SceneManager& sm) override;
  /**
   * @brief Fonction permettant la mise à jour de l'état interne de la scène
   *
   * @param delta le temps delta issue du timer
   * @param sm référence sur le gestionnaire de scène, permettant de
   * demander et d'acter un changement d'état
   */
  void update(f64 delta, SceneManager& sm) override;
  /**
   * @brief Rend les différents éléments de la scène sur l'objet Renderer
   *
   * @param renderer Référence sur le Renderer courant
   */
  void render(SDLW::Renderer& renderer) const override;
};

#endif