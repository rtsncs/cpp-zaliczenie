#pragma once

#include "mob.hpp"

class Player : public Mob {
  public:
    Player(Game *game);
    void update(float delta_time) override;
};
