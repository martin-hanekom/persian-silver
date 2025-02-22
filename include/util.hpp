#ifndef PERSIAN_SILVER_UTIL_HPP
#define PERSIAN_SILVER_UTIL_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

inline
float distance(sf::Vector2f const& a, sf::Vector2f const& b)
{
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

inline
sf::Color opaque(sf::Color color, uint8_t alpha)
{
    return {color.r, color.g, color.b, alpha};
}

#endif
