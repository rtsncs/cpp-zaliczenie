#include "mob.hpp"
#include "projectile.hpp"

Mob::Mob(Game *_game, sf::Texture *_texture, int _health, float _speed,
         int _collision_layer)
    : Sprite(_game, _texture, _collision_layer | CollisionLayer::MobLayer),
      item{nullptr}, health{_health}, movement_speed{_speed} {
    sprite.setRotation(90.0f);
}

bool Mob::is_dead() const { return dead; }

void Mob::take_damage(int dmg) {
    health -= dmg;
    if (health <= 0) {
        kill();
        if (item)
            item->kill();
    }
}

void Mob::heal(int heal) { health += heal; }

float Mob::get_speed() const { return movement_speed; }

int Mob::get_health() const { return health; }

void Mob::set_health(int _health) { health = _health; }

void Mob::pickup_item(Item *_item) {
    if (item)
        item->kill();

    item = _item;
    item->set_owner(this);
    item->teleport(position);
    item->rotate(direction);
}

void Mob::teleport(sf::Vector2f position) {
    if (item)
        item->teleport(position);
    Sprite::teleport(position);
}
unsigned Mob::move(sf::Vector2f offset) {
    unsigned id = Sprite::move(offset);
    if (id)
        return id;

    if (item)
        item->move(offset);
    return true;
}
void Mob::rotate(sf::Vector2f direction) {
    if (item)
        item->rotate(direction);
    Sprite::rotate(direction);
}
