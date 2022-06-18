#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <string>

sf::Texture *load_texture(std::string path);
sf::Font *load_font(std::string path);

template <typename T> inline float vec2_squared_len(sf::Vector2<T> vec) {
    return vec.x * vec.x + vec.y * vec.y;
}

template <typename T> inline float vec2_len(sf::Vector2<T> vec) {
    return std::sqrt(vec2_squared_len(vec));
}

template <typename T> inline sf::Vector2<T> vec2_normalize(sf::Vector2<T> vec) {
    return vec / vec2_len(vec);
}

template <typename T>
inline sf::Vector2<T> vec2_rotate(sf::Vector2<T> vec, float angle) {
    return sf::Vector2<T>(vec.x * std::cos(angle) - vec.y * std::sin(angle),
                          vec.x * std::sin(angle) + vec.y * std::cos(angle));
}
