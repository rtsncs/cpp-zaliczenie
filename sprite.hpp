#pragma once

#include "entity.hpp"

class Sprite : public Entity {
  public:
    virtual void update(float delta_time) = 0;
    virtual void teleport(sf::Vector2f position);
    virtual unsigned move(sf::Vector2f offset);
    virtual void rotate(sf::Vector2f direction);
    friend Game;

  protected:
    Sprite(Game *game, sf::Texture *texture, int collision_layer);
    sf::Sprite sprite;

  private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
