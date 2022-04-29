/**
 * @file Game.hpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 */

#ifndef H_TEMPEST_GAME_INC_GAMEOBJECT_
#define H_TEMPEST_GAME_INC_GAMEOBJECT_

// #include "../state/Scene.hpp"
#include "../state/SceneManager.hpp"
#include "../state/TitleScreen.hpp"
#include "../utils/types.hpp"
#include "RenderHandler.hpp"
#include <memory>

/**
 * @brief Classe gérant la logique du jeux
 *
 */
class Game
{
private:
  bool debug_flag_ = false;
  /**
   * @brief Structure de donnée comportant les informations de debug
   *
   */
  struct Debug
  {
    f64 inter_frame_delay_;
    f64 fps_;
  } debug_val_;
  bool run_ = true;
  static u16 WINDOWS_WIDTH_;
  static u16 WINDOWS_HEIGHT_;
  /**
   * @brief Le gestionnaire de scène
   *
   */
  SceneManager sm_;
  /**
   * @brief Le gestionnaire de rendu
   *
   */
  RenderHandler r_{ WINDOWS_WIDTH_, WINDOWS_HEIGHT_ };
  /**
   * @brief Function permettant l'arret de la simulation du jeu
   *
   */
  inline void stop_() { run_ = false; };

public:
  Game();
  /**
   * @brief Construit un objet de type jeu avec une fenêtre de rendu de taille
   * w_width * w_height
   *
   * @param w_width largeur de la fenêtre
   * @param w_height hauteur de la fenêtre
   */
  Game(u16 w_width, u16 w_height);
  ~Game();

  /**
   * @brief Efface la cible de rendu actuelle avec la couleur noire
   *
   */
  void clear();
  /**
   * @brief Gère les évènements au plus haut niveau, ces évènements sont
   * prioritaires sur tout le reste
   *
   */
  void processEvents();
  /**
   * \~french @brief Avance la simulation du jeu d'un point en appelant la
   * fonction de mise à jour de la scène courante
   *
   * \~french @param delta temps entre deux images, utilisé pour la simulation
   * de la physique
   *
   * \~english @brief Advances game simulation one step and runs the game
   * at a consistent speed despite differences in the underlying hardware
   *
   * \~english @param delta time between two images, used for game physics
   */
  void update(f64 delta);
  /**
   * @brief Rend la scène courante et l'affiche à l'écran
   *
   */
  void render();

  /**
   * @brief Retourne l'état de la  simulation du jeu
   *
   * @return true: le jeu est en train de tourner
   * @return false: le jeu à été arréter
   */
  bool isRunning() { return run_; };

  /**
   * @brief Retourne la largeur de la fenêtre ouverte lors de l'initialisation
   *
   * @return u16 largeur de la fenêtre
   */
  static u16 getWidth();
  /**
   * @brief Retourne la hauteur de la fenêtre ouverte lors de l'initialisation
   *
   * @return u16 hauteur de la fenêtre
   */
  static u16 getHeight();

  /**
   * @brief met à jour la variable contenant le délai inter image
   *
   * @param inter_frame_delay le délais inter image
   */
  void debugSetInterframeDelay(f64 inter_frame_delay);
  /**
   * @brief met à jour la valeur des fps (images par secondes)
   *
   * @param fps le nombre de fps (images par secondes)
   */
  void debugSetFPS(f64 fps);
};

#endif