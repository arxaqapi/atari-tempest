/**
 * @file Timer.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef H_TEMPEST_GAME_INC_TIMER_
#define H_TEMPEST_GAME_INC_TIMER_

#include "../sdlw/SDLW.hpp"
#include "Errors.hpp"
#include "types.hpp"
#include <random>

/**
 * @brief Type du timer utilisé, le timer PERFORMANCE utilise
 * une horloge de plus grande précision
 *
 */
enum class timer_type
{
  NORMAL,
  PERFORMANCE
};

/**
 * @brief Classe permettant de gérer la gestion du temps
 * et donc du nombre d'images par secondes de notre jeux
 *
 */
class Timer
{
private:
  timer_type t_;
  u32 max_ms_per_frame_;
  std::default_random_engine generator_;
  std::uniform_int_distribution<i32> distribution_;

  u64 start_;
  u64 stop_;
  f64 fps_;

public:
  /**
   * @brief Construction d'un nouvel objet Timer normal permettant de compter
   * le nombre de millisecondes qui sont passées
   * tout en limitant le temps maximum utilisé par images
   *
   * @param max_ms_per_frame nombre maximum de millisecondes autorisées par
   * image
   */
  Timer(u32 max_ms_per_frame);
  /**
   * @brief Construction d'un nouvel objet Timer de type t permettant de compter
   * le nombre de millisecondes qui sont passées
   * tout en limitant le temps maximum utilisé par images
   *
   * @param max_ms_per_frame nombre maximum de millisecondes autorisées par
   * image
   * @param t type d'horloge utilisé pour les calculs
   */
  Timer(u32 max_ms_per_frame, timer_type t);
  ~Timer();

  /**
   * @brief Lance l'horloge et stocke la valeur de l'horloge interne
   * 
   */
  void start();

  /**
   * @brief retourne le temps passé en ms entre le appels des méthodes start()
   * et stop()
   *
   * @return f64: valeur du temps passée
   */
  f64 stop();

  /**
   * @brief Retourne le nombre d'images par secondes auquel tourne le moteur,
   * avec pour limite le nombre maximum de millisecondes autorisées par image
   *
   * @return f64: valeur correspondant au nombre d'images par secondes calculées
   */
  f64 get_FPS();

  /**
   * @brief Affiche le nombre d'images par secondes à l'écran de façon lisible
   *
   */
  void print();

  /**
   * \~english @brief resets the internal stop_ counter after the variable delay
   * has been applied, allows to get the exact delay between 2 frames
   * for FPS caping
   * \~french @brief Remet à 0 la variable interne stop_ après que le délais
   * variable à été appliqué, permet d'obtenir le delai exact entre deux images
   * afin de limiter le nombre d'images par seconde
   *
   */
  f64 variable_delay();

  /**
   * \~english @brief Induces an artificial delay < max_ms_per_frame - 4
   * Mainly here to test clock mechanism like FPS caping
   * \~french @brief Introduit un délai artificiel à des fins de débogage.
   * Permets de tester le mécanisme de limitation du nombres d'images par
   * seconde
   */
  void artificial_delay();
};

#endif