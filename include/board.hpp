#ifndef PERSIAN_SILVER_BOARD_HPP
#define PERSIAN_SILVER_BOARD_HPP

#include <optional>
#include <SFML/Graphics.hpp>
#include "tile.hpp"

class Board
{
public:
    Board(size_t depth);
    void draw() const;
    void onMouseMoved(sf::Vector2f mousePosition);
    void onLeftClick();
    void onRightClick();
    Tile* center();
    Tile* getStartPos(size_t index);

private:
    size_t depth;
    std::vector<Tile> tiles;
    Tile* hovering = nullptr;
    Tile* selected = nullptr;
};

#endif