#include "gun.hpp"
#include "mob.hpp"
#include "projectile.hpp"
#include "utils.hpp"

Gun *Gun::Pistol(Game *game) {
    return new Gun(game, 0.25f, 550.0f, sf::Vector2f(26.0f, 21.5f), 10.0f);
}

Gun *Gun::SMG(Game *game) {
    return new Gun(game, 0.1f, 800.0f, sf::Vector2f(26.0f, 21.5f), 15.0f);
}

Gun::Gun(Game *game, float _shot_cooldown, float _bullet_speed,
         sf::Vector2f _bullet_offset, int _damage)
    : Item(game), shot_cooldown{_shot_cooldown}, bullet_speed{_bullet_speed},
      bullet_offset{_bullet_offset}, damage{_damage} {}

void Gun::use() {
    if (last_shot.getElapsedTime().asSeconds() >= shot_cooldown) {
        last_shot.restart();
        float angle = std::atan2(direction.y, direction.x);
        int bullet_layer =
            owner->get_collision_layer() & CollisionLayer::PlayerLayer
                ? CollisionLayer::EnemyLayer
                : CollisionLayer::PlayerLayer;
        auto projectile =
            new Projectile(game, bullet_speed, damage, bullet_layer);
        projectile->teleport(position + vec2_rotate(bullet_offset, angle));
        projectile->rotate(direction);
        game->spawn(projectile);
    }
}

void Gun::update([[maybe_unused]] float delta_time){};
