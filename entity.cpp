#include "entity.hpp"
#include "utils.hpp"

Entity::Entity(Game *_game, int _collision_layer)
    : game{_game}, entity_id{game->new_entity_id()}, position{sf::Vector2f(
                                                         0.0f, 0.0f)},
      direction{sf::Vector2f(1.0f, 0.0f)}, dead{false}, collision_layer{
                                                            _collision_layer} {}

Entity::~Entity() {}

void Entity::teleport(sf::Vector2f _position) { position = _position; }

unsigned Entity::move(sf::Vector2f offset) {
    auto new_position = position + offset;
    auto new_box = bounding_box;
    new_box.left += new_position.x - new_box.width / 2.0f;
    new_box.top += new_position.y - new_box.height / 2.0f;

    auto world_size = game->get_world_size();
    if (new_position.x > world_size.x || new_position.y > world_size.y ||
        new_position.x < 0.0f || new_position.y < 0.0f) {
        return -1;
    }
    unsigned id = game->collision_check(new_box, entity_id, collision_layer);
    if (id)
        return id;

    position = new_position;

    return 0;
}

void Entity::rotate(sf::Vector2f _direction) { direction = _direction; }

sf::Vector2f Entity::get_pos() const { return position; }

bool Entity::is_dead() const { return dead; }

void Entity::kill() { dead = true; }

sf::FloatRect Entity::get_bounding_box() const {
    auto box = bounding_box;
    box.left += position.x - box.width / 2.0f;
    box.top += position.y - box.height / 2.0f;
    return box;
}
int Entity::get_collision_layer() const { return collision_layer; }
unsigned Entity::get_id() const { return entity_id; }

void Entity::draw(sf::RenderTarget &target,
                  [[maybe_unused]] sf::RenderStates states) const {
    if (game->get_debug_mode()) {
        auto box = get_bounding_box();
        sf::RectangleShape shape(sf::Vector2f(box.width, box.height));
        shape.setPosition(box.left, box.top);
        shape.setFillColor(sf::Color(0, 0, 0, 0));
        shape.setOutlineColor(sf::Color(255, 255, 255));
        shape.setOutlineThickness(-1);
        target.draw(shape);
    }
}
