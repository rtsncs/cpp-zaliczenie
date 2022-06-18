#pragma once

#include "mob.hpp"

class Enemy : public Mob {
  private:
    int score;
    Enemy(Game *game, int health, float speed, int score);

  public:
    void update(float delta_time) override;
    static Enemy *Pistol(Game *game);
    void kill() override;
    ~Enemy() override;
};
