#ifndef PERSIAN_SILVER_BOARD_HPP
#define PERSIAN_SILVER_BOARD_HPP

#include <cmath>
#include <cstdlib>
#include <SFML/Graphics.hpp>

class Tile
{
public:
    Tile(sf::Vector2f pos, int depth);
    void draw() const;
    void setNeighbor(size_t index, Tile& neighbor);
    Tile* getNeighbor(size_t index);
    bool hasNeighbor(size_t index) const;
    bool touches(sf::Vector2f point) const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getNeigborPosition(size_t index) const;
    void setPosition(sf::Vector2f position);

    void clear();
    void onHover();

    static constexpr size_t tileSides = 6;
    static constexpr float tileRadius = 50.f;
    static constexpr float tilePadding = -3.f;
    static constexpr float tileRotation = M_PI / tileSides;

    int const depth;

private:
    static constexpr size_t opposite(size_t index);

    sf::CircleShape shape;
    sf::Text text;
    std::array<Tile*, tileSides> neighbors;
};

class Board
{
public:
    Board(size_t depth);
    void draw() const;
    void clear();
    void onMouseMoved(sf::Vector2f mousePosition);

private:
    size_t depth;
    std::vector<Tile> tiles;
};

#endif