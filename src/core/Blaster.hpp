//
// Created by massimo on 23/03/2022.
//

#ifndef TEMPEST_ATARI_BLASTER_HPP
#define TEMPEST_ATARI_BLASTER_HPP

#include "GameObject.hpp"
#include "Bullet.hpp"
#include "GameObjectPool.hpp"
#include "../utils/Delay.hpp"

class Blaster: public GameObject
{
private:
  static const u8 MAX_BULLETS_ = 100;
  static constexpr f64 SHOOT_DELAY_ = 150;
  u8 max_health_{3};
  u8 health_{max_health_};
  bool is_shooting_{false};
  GameObjectPool<Bullet> bullets_{MAX_BULLETS_};
  Delay shoot_delay_{SHOOT_DELAY_};

public:
  Blaster() = default;
  Blaster(const Blaster &blaster) = default;
  ~Blaster() override = default;

  void shoot();
  void stopShooting();
  void render(SDL_Renderer *renderer, const Map &map) const override;
  void update(f64 delta, const Map& map) override;
};

#endif // TEMPEST_ATARI_BLASTER_HPP
