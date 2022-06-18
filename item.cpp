#include "item.hpp"

Item::Item(Game *game) : Entity(game, CollisionLayer::ItemLayer) {}

void Item::set_owner(Mob *_owner) { owner = _owner; }
