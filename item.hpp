#pragma once

#include "entity.hpp"
class Mob;

class Item : public Entity {
  public:
    virtual void use() = 0;
    void set_owner(Mob *owner);
    void update(float delta_time) override = 0;

  protected:
    Item(Game *game);
    Mob *owner;

  private:
    void draw([[maybe_unused]] sf::RenderTarget &target,
              [[maybe_unused]] sf::RenderStates states) const override {}
};
