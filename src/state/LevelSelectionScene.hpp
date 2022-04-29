/**
 * @file LevelSelectionScene.hpp
 * @author Massimo, Tarek Kunze (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef H_TEMPEST_GAME_INC_SCENE_LEVEL_SELECT_
#define H_TEMPEST_GAME_INC_SCENE_LEVEL_SELECT_

#include "../ui/UILevelBox.hpp"
#include "../ui/UILevelCarousel.hpp"
#include "Scene.hpp"
#include <filesystem>

class SceneManager;

/**
 * @brief Classe définissant la logique propre à la scène permettant la
 * sélection du niveau de jeu souhaité
 *
 */
class LevelSelectionScene : public Scene
{
private:
  /**
   * @brief Element d'interface permettant la sélection du niveau de jeu
   * souhaité
   *
   */
  UILevelCarousel ui_level_carousel_;

public:
  LevelSelectionScene();
  ~LevelSelectionScene();

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