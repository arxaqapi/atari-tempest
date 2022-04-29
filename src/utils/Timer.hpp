/**
 * @file Timer.hpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
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
enum class TimerType
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
template<TimerType T>
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
  f64 getFPS();

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
  f64 variableDelay();

  /**
   * \~english @brief Induces an artificial delay < max_ms_per_frame - 4
   * Mainly here to test clock mechanism like FPS caping
   * \~french @brief Introduit un délai artificiel à des fins de débogage.
   * Permets de tester le mécanisme de limitation du nombres d'images par
   * seconde
   */
  void artificialDelay();
};

// Util function

inline f64
toMs(f64 value)
{
  auto freq_in_ms = static_cast<f64>(SDLW::GetPerformanceFrequency()) / 1000.;
  return value / freq_in_ms;
}

// Template implementation

template<TimerType T>
Timer<T>::Timer(u32 max_ms_per_frame)
  : max_ms_per_frame_(max_ms_per_frame)
  , distribution_{ 0, static_cast<i32>(max_ms_per_frame) - 4 }
  , start_{ 0 }
  , stop_{ 0 }
  , fps_{ 0.0 }
{}

template<TimerType T>
Timer<T>::~Timer()
{}
template<TimerType T>
void
Timer<T>::start()
{
  if constexpr (T == TimerType::NORMAL)
    start_ = SDLW::GetTicks64();
  else if constexpr (T == TimerType::PERFORMANCE)
    start_ = SDLW::GetPerformanceCounter();
  else
    throw errors::NotImplemented();
}

template<TimerType T>
f64
Timer<T>::stop()
{
  if constexpr (T == TimerType::NORMAL) {
    stop_ = SDLW::GetTicks64();
    return stop_ - start_;
  } else if constexpr (T == TimerType::PERFORMANCE) {
    stop_ = SDLW::GetPerformanceCounter();
    return toMs(stop_ - start_);
  } else
    throw errors::NotImplemented();
}

template<TimerType T>
f64
Timer<T>::getFPS()
{
  if constexpr (T == TimerType::NORMAL) {
    return 1. / ((stop_ - start_) / 1000.);
  } else if constexpr (T == TimerType::PERFORMANCE) {
    return 1. / ((toMs(stop_ - start_) / 1000.));
  } else
    throw errors::NotImplemented();
}

template<TimerType T>
void
Timer<T>::print()
{
  std::cout << "[Log] - FPS = " << getFPS() << std::endl;
}

template<TimerType T>
f64
Timer<T>::variableDelay()
{
  u64 ms_elapsed;
  if constexpr (T == TimerType::NORMAL) {
    ms_elapsed = stop_ - start_;
  } else if constexpr (T == TimerType::PERFORMANCE) {
    ms_elapsed = toMs(stop_ - start_);
  } else {
    throw errors::NotImplemented();
  }
  auto del = max_ms_per_frame_ - ms_elapsed;
  assert(del <= max_ms_per_frame_ && "Computed delay is way too big");
  SDLW::Delay(del);
  return this->stop();
}

template<TimerType T>
void
Timer<T>::artificialDelay()
{
  auto r = static_cast<u32>(distribution_(generator_));
  assert(r < max_ms_per_frame_);
  SDLW::Delay(r);
}

#endif