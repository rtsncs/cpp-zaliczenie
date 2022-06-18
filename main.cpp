#include "game.hpp"
#include <iostream>

int main() {
    Game *game;
    try {
        game = new Game;
    } catch (std::string e) {
        std::cerr << e << std::endl;
        return 1;
    }

    game->run();
    return 0;
}
