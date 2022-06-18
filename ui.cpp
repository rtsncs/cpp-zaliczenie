#include "ui.hpp"

void Text::draw(sf::RenderTarget &target,
                [[maybe_unused]] sf::RenderStates states) const {
    target.draw(text);
    Entity::draw(target, states);
}

Text::Text(Game *game, std::string _label, Alignment _alignment)
    : Entity(game, CollisionLayer::UILayer), text{sf::Text(_label,
                                                           *game->get_font())},
      label{_label}, alignment{_alignment} {
    bounding_box = text.getLocalBounds();
    if (alignment == Alignment::Center) {
        text.setOrigin(bounding_box.width / 2.0f, bounding_box.height / 2.0f);
    }
}

void Text::teleport(sf::Vector2f _position) {
    Entity::teleport(_position);
    text.setPosition(position);
}

unsigned Text::move(sf::Vector2f offset) {
    unsigned hit = Entity::move(offset);
    if (hit)
        return hit;
    text.setPosition(position);
    return 0;
}

void Text::rotate(sf::Vector2f _direction) {
    Entity::rotate(_direction);
    float angle = std::atan2(direction.y, direction.x);
    text.setRotation(angle * 180.0f / M_PI);
}

void Text::update([[maybe_unused]] float delta_time) {}

sf::FloatRect Text::get_bounding_box() const {
    auto box = bounding_box;
    if (alignment == Alignment::Center) {
        box.left += position.x - box.width / 2.0f;
        box.top += position.y - box.height / 2.0f;
    } else {
        box.left += position.x;
        box.top += position.y;
    }
    return box;
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(background);
    Text::draw(target, states);
}

Button::Button(Game *game, std::string label, Alignment alignment)
    : Text(game, label, alignment), background{sf::RectangleShape()} {
    const float offset = 5.0f;
    bounding_box.height += 2.0f * offset;
    bounding_box.width += 2.0f * offset;
    background.setSize(sf::Vector2f(bounding_box.width, bounding_box.height));
    background.setFillColor(sf::Color(0, 0, 0, 128));
    if (alignment == Alignment::Center) {
        background.setOrigin(bounding_box.width / 2.0f - bounding_box.left,
                             bounding_box.height / 2.0f - bounding_box.top);
    }
}

bool Button::clicked() {
    if (game->get_window()->hasFocus() &&
        sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        auto mouse_pos = sf::Mouse::getPosition(*game->get_window());
        return get_bounding_box().contains(mouse_pos.x, mouse_pos.y);
    }
    return false;
}

std::string Button::get_label() { return label; }

void Button::teleport(sf::Vector2f _position) {
    Text::teleport(_position);
    background.setPosition(position);
}

unsigned Button::move(sf::Vector2f offset) {
    unsigned hit = Text::move(offset);
    if (hit)
        return hit;
    background.setPosition(position);
    return 0;
}

void Button::rotate(sf::Vector2f _direction) {
    Text::rotate(_direction);
    float angle = std::atan2(direction.y, direction.x);
    background.setRotation(angle * 180.0f / M_PI);
}
