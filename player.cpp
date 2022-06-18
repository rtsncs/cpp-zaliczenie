#include "player.hpp"
#include "utils.hpp"

Player::Player(Game *game)
    : Mob(game, game->get_player_texture(), 100, 400.0f,
          CollisionLayer::PlayerLayer) {}

void Player::update(float delta_time) {
    if (game->get_window()->hasFocus()) {
        sf::Vector2f movement;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            movement.x -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            movement.x += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            movement.y -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            movement.y += 1;

        if (vec2_squared_len(movement) != 0.0f) {
            move(vec2_normalize(movement) * get_speed() * delta_time);
        }

        sf::Vector2f rotation;
        auto mouse_pos = sf::Mouse::getPosition(*(game->get_window()));
        rotate(
            vec2_normalize(sf::Vector2f(mouse_pos.x, mouse_pos.y) - position));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && item)
            item->use();
    }
}
