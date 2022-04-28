/**
 * @file Delay.hpp
 * @author massimo
 * @version 0.1
 * @date 2022-03-25
 *
 * @copyright Copyright (c) 2022
 */

#ifndef TEMPEST_ATARI_DELAY_HPP
#define TEMPEST_ATARI_DELAY_HPP

#include "types.hpp"

/**
 * @brief Classe utilitaire pour gérer des délais
 */
class Delay
{
private:
  /**
   * Temps minimal pour que le délai soit complet
   */
  f64 min_delay_ = 0;

  /**
   * Délai en cours
   */
  f64 current_delay_ = min_delay_;

public:
  Delay() = default;
  Delay(const Delay& delay) = default;
  explicit Delay(f64 min_delay)
    : min_delay_{ min_delay }
  {}
  ~Delay() = default;

  /**
   * @brief Réinitialise le délai en cours
   */
  inline void reset() { current_delay_ = 0; }

  /**
   * @brief Teste si le délai en cours est complet
   * @return Vrai si le délai est complet, faux sinon
   */
  inline bool complete() const { return current_delay_ > min_delay_; }

  /**
   * @brief Met à jour le délai en cours
   * @param delta Temps passé depuis le dernier appel
   */
  inline void update(f64 delta) { current_delay_ += delta; }
};

#endif // TEMPEST_ATARI_DELAY_HPP
