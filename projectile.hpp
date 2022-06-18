#pragma once

#include "sprite.hpp"

class Projectile : public Sprite {
  private:
    float speed;
    int damage;

  public:
    Projectile(Game *game, float speed, int damage, int collision_layer);
    void update(float delta_time) override;
};
