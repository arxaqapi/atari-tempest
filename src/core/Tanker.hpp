//
// Created by massimo on 16/04/2022.
//

#ifndef TEMPEST_ATARI_TANKER_HPP
#define TEMPEST_ATARI_TANKER_HPP

#include "GameObject.hpp"

/**
 * @brief Représente le Tanker
 */
class Tanker : public GameObject
{
private:
  /**
   * @brief Booléen indiquant si le Tanker s'est séparé pour faire apparaître deux
   * Flippers
   */
  bool split_ = false;

public:
  Tanker();
  Tanker(const Tanker& tanker) = default;
  ~Tanker() override = default;

  void render(SDLW::Renderer& renderer,
              const Map& map,
              const color& render_color) const override;
  void update(f64 delta, const Map& map) override;

  /**
   * Getters
   */
  inline bool isSplit() const { return split_; }

  /**
   * Setters
   */
  inline void setSplit(bool split) { split_ = split; }
};

#endif // TEMPEST_ATARI_TANKER_HPP
