#include "utils.hpp"

sf::Texture *load_texture(std::string path) {
    sf::Texture *texture = new sf::Texture();
    if (!texture->loadFromFile(path)) {
        throw "Error loading file " + path;
    }
    return texture;
}

sf::Font *load_font(std::string path) {
    sf::Font *font = new sf::Font();
    if (!font->loadFromFile(path)) {
        throw "Error loading file " + path;
    }
    return font;
}
