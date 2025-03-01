#ifndef PERSIAN_SILVER_BOARD_HPP
#define PERSIAN_SILVER_BOARD_HPP

#include <optional>
#include <SFML/Graphics.hpp>
#include "ui.hpp"
#include "tile.hpp"

namespace silver
{

class Board : public Interaction
{
public:
    Board(size_t depth);

    void draw() const;

    bool onMouseMoved(sf::Vector2f mousePos) override;
    bool onLeftClick() override;
    bool onRightClick() override;
    bool touches(sf::Vector2f mousePos) const override;

    BoardTile* center();
    BoardTile* getStartPos(size_t index);

    BoardTile* hovering = nullptr;
    BoardTile* selected = nullptr;

private:
    void construct();

    size_t depth;
    std::vector<BoardTile> tiles;
};

}

#endif