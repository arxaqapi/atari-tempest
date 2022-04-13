//
// Created by massimo on 23/03/2022.
//

#ifndef TEMPEST_ATARI_BLASTER_HPP
#define TEMPEST_ATARI_BLASTER_HPP

#include "../utils/Delay.hpp"
#include "Bullet.hpp"
#include "GameObject.hpp"
#include "GameObjectPool.hpp"

class Blaster : public GameObject
{
private:
  static const u8 MAX_BULLETS_ = 100;
  static constexpr f64 SHOOT_DELAY_ = 150;
  static constexpr u8 MAX_HEALTH_ = 3;
  static constexpr f64 MOVE_DELAY_ = 50;
  u8 health_{ MAX_HEALTH_ };
  u32 score_{ 0 };
  bool is_shooting_{ false };

private:
  GameObjectPool<Bullet> bullets_{ MAX_BULLETS_ };
  Delay shoot_delay_{ SHOOT_DELAY_ };

public:
  Blaster() = default;
  explicit Blaster(const Map& map);
  Blaster(const Blaster& blaster) = default;
  ~Blaster() override = default;

  std::vector<Bullet>& getBullets();
  u8 getHealth() const;
  u32 getScore() const;
  void addScore(u32 score);
  void shoot();
  void stopShooting();
  void hit() override;
  void render(SDL_Renderer* renderer, const Map& map) const override;
  void update(f64 delta, const Map& map) override;
  void clear();
};

#endif // TEMPEST_ATARI_BLASTER_HPP
