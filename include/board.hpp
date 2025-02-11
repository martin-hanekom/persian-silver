#ifndef PERSIAN_SILVER_BOARD_HPP
#define PERSIAN_SILVER_BOARD_HPP

#include <cstdlib>
#include <SFML/Graphics.hpp>

class Tile
{
public:
    Tile(sf::Vector2f const position);
    void draw() const;

private:
    sf::CircleShape shape;
    static constexpr float tileRadius = 100.f;
    static constexpr sf::Angle tileRotation = sf::radians(3.1415f / 6.f);
};

class Sector
{

};

class Board
{
public:
    Board(size_t depth);
    void draw() const;

private:
    size_t depth;
    Tile center;
};

#endif