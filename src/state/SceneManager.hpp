/**
 * @file SceneManager.hpp
 * @author Tarek Kunze (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */
#ifndef H_TEMPEST_GAME_INC_SCENEMANAGER_
#define H_TEMPEST_GAME_INC_SCENEMANAGER_

#include "GameScene.hpp"
#include "Scene.hpp"
#include "TitleScreen.hpp"
#include <memory>

/**
 * \~french @brief énumération des états possible de la machine à état
 *
 */
enum State
{
  STATE_TITLE_SCREEN,
  STATE_LEVEL_SELECT,
  STATE_GAME_SCENE,
  STATE_PAUSE_MENU,
  STATE_WIN_SCREEN,
  STATE_DEATH_SCREEN
};

/**
 * \~french @brief Machine à état gérant la transition entre les scènes
 *
 */
class SceneManager
{
private:
  /**
   * \~french @brief pointeur unique sur la scène actuelle
   *
   */
  std::unique_ptr<Scene> current_scene_p_ = std::make_unique<TitleScreen>();
  State current_state_ = STATE_TITLE_SCREEN;
  State next_state_ = STATE_TITLE_SCREEN;
  /**
   * \~french @brief Le niveau demandé lors de l'initialisation de la scène de
   * jeu: STATE_GAME_SCENE
   *
   */
  i32 requested_level_ = 0;

  /**
   * \~english @brief Destroys the current scene object and affects the new
   * requested one
   * \~french @brief Détruit et libère la mémoire de la scène courante et
   * affecte la nouvelle
   *
   */
  void switchScene();
  /**
   * \~french @brief Retourne le pointeur sur la scène suivante d'après l'état
   * passé en paramètre
   *
   * \~french @param state Le prochain état demandé
   * \~french @return std::unique_ptr<Scene> pointeur unique sur la scène
   * suivante
   */
  std::unique_ptr<Scene> getCorrespondingScene(State state);

public:
  /**
   * \~french @brief Construit le gestionnaire de scène
   *
   */
  SceneManager();
  ~SceneManager();

  /**
   * \~french @brief Met à jour la variable correspondant au prochain état
   * demandé et vérifie si la transition est autorisée
   *
   * \~french @param next_requested_state Le prochain état demandé
   *
   * \~english @brief Set the next state variable to the requested next state
   * and checks if the switch is authorized
   *
   * \~english @param next_requested_state Le prochain état demandé
   */
  void setNextState(State next_requested_state);

  /**
   * \~french @brief Mets à jour la variable du prochain état demandé ainsi que
   * le niveau demandé
   *
   * \~french @param next_requested_state le prochain état demandée
   * \~french @param level le niveau du jeu demandé
   */
  void setNextState(State next_requested_state, i32 level);

  /**
   * \~french @brief Getter sur la Scene courante
   *
   * \~french @return Scene& Renvoie une référence sur la scène courante
   */
  Scene& getCurrentScene() { return *current_scene_p_; }

  /**
   * \~french @brief Met à jour la scène si une transition à été demandé
   *
   * \~french @param delta le temps delta issue du timer
   */
  void update(f64 delta);
};

#endif