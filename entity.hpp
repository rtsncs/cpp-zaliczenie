#pragma once
#include "game.hpp"
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
  public:
    virtual void teleport(sf::Vector2f position);
    virtual unsigned move(sf::Vector2f offset);
    virtual void rotate(sf::Vector2f direction);
    sf::Vector2f get_pos() const;
    virtual void update(float delta_time) = 0;
    bool is_dead() const;
    virtual void kill();
    virtual sf::FloatRect get_bounding_box() const;
    int get_collision_layer() const;
    unsigned get_id() const;
    friend Game;
    virtual ~Entity();

  protected:
    Entity(Game *game, int collision_layer);
    Game *game;
    unsigned entity_id;
    sf::Vector2f position;
    sf::Vector2f direction;
    bool dead;
    sf::FloatRect bounding_box;
    int collision_layer;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
