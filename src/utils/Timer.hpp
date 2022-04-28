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
#include <cassert>
#include <iostream>
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
// TODO: make a specific template class
template<timer_type T>
class Timer
{
private:
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

// Util function

inline f64
to_ms(f64 value)
{
  auto freq_in_ms = static_cast<f64>(SDLW::GetPerformanceFrequency()) / 1000.;
  return value / freq_in_ms;
}

// Template implementation

template<timer_type T>
Timer<T>::Timer(u32 max_ms_per_frame)
  : max_ms_per_frame_(max_ms_per_frame)
  , distribution_{ 0, static_cast<i32>(max_ms_per_frame) - 4 }
  , start_{ 0 }
  , stop_{ 0 }
  , fps_{ 0.0 }
{}

template<timer_type T>
Timer<T>::~Timer()
{}
template<timer_type T>
void
Timer<T>::start()
{
  if constexpr (T == timer_type::NORMAL)
    start_ = SDLW::GetTicks64();
  else if constexpr (T == timer_type::PERFORMANCE)
    start_ = SDLW::GetPerformanceCounter();
  else
    throw errors::not_implemented();
}

template<timer_type T>
f64
Timer<T>::stop()
{
  if constexpr (T == timer_type::NORMAL) {
    stop_ = SDLW::GetTicks64();
    return stop_ - start_;
  } else if constexpr (T == timer_type::PERFORMANCE) {
    stop_ = SDLW::GetPerformanceCounter();
    return to_ms(stop_ - start_);
  } else
    throw errors::not_implemented();
}

template<timer_type T>
f64
Timer<T>::get_FPS()
{
  if constexpr (T == timer_type::NORMAL) {
    return 1. / ((stop_ - start_) / 1000.);
  } else if constexpr (T == timer_type::PERFORMANCE) {
    return 1. / ((to_ms(stop_ - start_) / 1000.));
  } else
    throw errors::not_implemented();
}

template<timer_type T>
void
Timer<T>::print()
{
  std::cout << "[Log] - FPS = " << get_FPS() << std::endl;
}

template<timer_type T>
f64
Timer<T>::variable_delay()
{
  u64 ms_elapsed;
  if constexpr (T == timer_type::NORMAL) {
    ms_elapsed = stop_ - start_;
  } else if constexpr (T == timer_type::PERFORMANCE) {
    ms_elapsed = to_ms(stop_ - start_);
  } else {
    throw errors::not_implemented();
  }
  auto del = max_ms_per_frame_ - ms_elapsed;
  assert(del <= max_ms_per_frame_ && "Computed delay is way too big");
  SDLW::Delay(del);
  return this->stop();
}

template<timer_type T>
void
Timer<T>::artificial_delay()
{
  auto r = static_cast<u32>(distribution_(generator_));
  assert(r < max_ms_per_frame_);
  SDLW::Delay(r);
}

#endif