#pragma once

#include "item.hpp"
#include "sprite.hpp"

class Mob : public Sprite {
  protected:
    Item *item;
    int health;
    float movement_speed;
    bool dead;
    Mob(Game *game, sf::Texture *texture, int health, float speed,
        int collision_layer);

  public:
    bool is_dead() const;
    void take_damage(int dmg);
    void heal(int heal);
    float get_speed() const;
    int get_health() const;
    void pickup_item(Item *item);
    void set_health(int health);

    void teleport(sf::Vector2f position);
    unsigned move(sf::Vector2f offset);
    void rotate(sf::Vector2f direction);
    friend Game;
};
