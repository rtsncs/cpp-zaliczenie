#include "projectile.hpp"
#include "mob.hpp"

Projectile::Projectile(Game *game, float _speed, int _damage,
                       int _collision_layer)
    : Sprite(game, game->get_bullet_texture(),
             _collision_layer | CollisionLayer::BulletLayer),
      speed{_speed}, damage{_damage} {}

void Projectile::update(float delta_time) {
    unsigned hit = move(direction * speed * delta_time);
    if (hit) {
        kill();
        auto hit_entity = dynamic_cast<Mob *>(game->get_entity(hit));
        if (hit_entity) {
            hit_entity->take_damage(damage);
        }
    }
}
