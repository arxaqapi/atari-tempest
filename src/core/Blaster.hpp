/**
 * @file Blaster.hpp
 * @author massimo
 * @version 0.1
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2022
 */

#ifndef TEMPEST_ATARI_BLASTER_HPP
#define TEMPEST_ATARI_BLASTER_HPP

#include "../sdlw/SDLW.hpp"
#include "../utils/Delay.hpp"
#include "Bullet.hpp"
#include "GameObject.hpp"
#include "GameObjectPool.hpp"

/**
 * @brief Représente le Blaster
 */
class Blaster : public GameObject
{
private:
  static const u8 MAX_BULLETS_ = 100;
  static constexpr f64 SHOOT_DELAY_ = 120;
  static constexpr u8 MAX_HEALTH_ = 3;
  u8 health_ = MAX_HEALTH_;
  u32 score_ = 0;
  bool is_shooting_ = false;
  GameObjectPool<Bullet> bullets_{ MAX_BULLETS_ };
  Delay shoot_delay_{ SHOOT_DELAY_ };

public:
  Blaster() = default;
  Blaster(const Blaster& blaster) = default;
  ~Blaster() override = default;

  /**
   * @brief Réinitialise les attributs de classe
   */
  void clear();

  /**
   * @brief Ajoute le score au score courant
   * @param score Score à ajouter
   */
  inline void addScore(u32 score) { score_ += score; }

  void render(SDLW::Renderer& renderer,
              const Map& map,
              const color& render_color) const override;
  void update(f64 delta, const Map& map) override;

  inline void hit() override
  {
    health_ = std::max(health_ - 1, 0);
    clear();
  }

  /**
   * Setters
   */
  inline void shoot() { is_shooting_ = true; }
  inline void stopShooting() { is_shooting_ = false; }

  /**
   * Getters
   */
  inline std::vector<Bullet>& getBullets() { return bullets_.getPool(); }
  inline u8 getHealth() const { return health_; }
  inline u32 getScore() const { return score_; }
};

#endif // TEMPEST_ATARI_BLASTER_HPP
