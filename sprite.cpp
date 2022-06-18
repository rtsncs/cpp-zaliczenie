#include "sprite.hpp"
#include "utils.hpp"

Sprite::Sprite(Game *_game, sf::Texture *_texture, int _collision_layer)
    : Entity(_game, _collision_layer), sprite{sf::Sprite(*_texture)} {
    sprite.setPosition(position.x, position.y);
    sprite.setOrigin(_texture->getSize().x / 2.0f,
                     _texture->getSize().y / 2.0f);
    rotate(direction);
    sprite.setScale(2.0f, 2.0f);
    bounding_box = sprite.getLocalBounds();
    bounding_box.width *= 2.0f;
    bounding_box.height *= 2.0f;
}

void Sprite::draw(sf::RenderTarget &target,
                  [[maybe_unused]] sf::RenderStates states) const {
    target.draw(sprite);
    Entity::draw(target, states);
}

void Sprite::teleport(sf::Vector2f _position) {
    Entity::teleport(_position);
    sprite.setPosition(position);
}

unsigned Sprite::move(sf::Vector2f offset) {
    unsigned hit = Entity::move(offset);
    if (hit)
        return hit;

    sprite.setPosition(position);
    return 0;
}

void Sprite::rotate(sf::Vector2f _direction) {
    Entity::rotate(_direction);
    float angle = std::atan2(direction.y, direction.x);
    sprite.setRotation(angle * 180.0f / M_PI);
}
