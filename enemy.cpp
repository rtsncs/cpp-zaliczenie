#include "enemy.hpp"
#include "gun.hpp"
#include "player.hpp"
#include "utils.hpp"

Enemy::Enemy(Game *game, int health, float speed, int _score)
    : Mob(game, game->get_enemy_texture(), health, speed,
          CollisionLayer::EnemyLayer),
      score{_score} {}

Enemy::~Enemy() { delete item; }

void Enemy::update(float delta_time) {
    if (game->get_state() == GameState::Running) {
        auto player_pos = game->get_player()->get_pos();
        rotate(vec2_normalize(player_pos - position));
        move(direction * movement_speed * delta_time);
        if (item)
            item->use();
    }
}

Enemy *Enemy::Pistol(Game *game) {
    auto enemy = new Enemy(game, 50, 200.0f, 50);
    enemy->pickup_item(Gun::Pistol(game));
    return enemy;
}

void Enemy::kill() {
    game->add_score(score);
    game->add_kill();
    Mob::kill();
}
