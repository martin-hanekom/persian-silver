#include "board.hpp"
#include "screen.hpp"

Tile::Tile(sf::Vector2f const position)
{
    shape.setRadius(Tile::tileRadius);
    shape.setPointCount(6);
    shape.setOrigin({Tile::tileRadius, Tile::tileRadius});
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(position);
    shape.setRotation(Tile::tileRotation);
}

void Tile::draw() const
{
    Screen::draw(shape);
}

Board::Board(size_t depth)
    : depth(depth), center({0.f, 0.f})
{
}

void Board::draw() const
{
    center.draw();
}