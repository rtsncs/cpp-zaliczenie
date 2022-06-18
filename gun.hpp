#pragma once

#include "item.hpp"

class Gun : public Item {
  public:
    void use() override;
    void update(float delta_time) override;
    static Gun *Pistol(Game *game);
    static Gun *SMG(Game *game);

  private:
    Gun(Game *game, float bullet_speed, float shot_cooldown,
        sf::Vector2f bullet_offset, int damage);
    float shot_cooldown;
    sf::Clock last_shot;
    float bullet_speed;
    sf::Vector2f bullet_offset;
    int damage;
};
