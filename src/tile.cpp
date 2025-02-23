#include <cmath>
#include "tile.hpp"
#include "game.hpp"
#include "action.hpp"

namespace silver
{

void Tile::setPiece(Piece* piece)
{
    this->piece = piece;
}

Piece* Tile::getPiece()
{
    return piece;
}

bool Tile::hasPiece() const
{
    return piece != nullptr;
}


BoardTile::BoardTile(sf::Vector2f pos, int depth)
    : Circle(pos, tileRadius, tileSides, true), depth(depth)
{
    setFillColor(std::rand() % 2 ? lightGrass : darkGrass);
    setHoverColor(defaultHoverColor);
    shape.setRotation(sf::radians(tileRotation));
}

void BoardTile::setNewNeighbor(size_t index, BoardTile* other)
{
    assert(nullptr != other);
    neighbors[index] = other;
    other->setNeighbor(opposite(index), this);

    auto leftIndex = (index + tileSides - 1) % tileSides;
    auto rightIndex = (index + 1) % tileSides;
    if (auto left = getNeighbor(leftIndex); left != nullptr)
    {
        auto leftNeighborIndex = (opposite(leftIndex) + tileSides - 1) % tileSides;
        left->setNeighbor(leftNeighborIndex, other);
        other->setNeighbor(opposite(leftNeighborIndex), left);
    }

    if (auto right = getNeighbor(rightIndex); right != nullptr)
    {
        auto rightNeighborIndex = (opposite(rightIndex) + 1) % tileSides;
        right->setNeighbor(rightNeighborIndex, other);
        other->setNeighbor(opposite(rightNeighborIndex), right);
    }
}

void BoardTile::setNeighbor(size_t index, BoardTile* other)
{
    neighbors[index] = other;
}

BoardTile* BoardTile::getNeighbor(size_t index)
{
    return hasNeighbor(index) ? neighbors[index] : nullptr;
}

bool BoardTile::hasNeighbor(size_t index) const
{
    return neighbors[index] != nullptr;
}

sf::Vector2f BoardTile::getNeigborPosition(size_t index) const
{
    auto position = shape.getPosition();
    position.x += 2 * (tileRadius + tilePadding) * std::sin(2 * M_PI * index / tileSides);
    position.y += -2 * (tileRadius + tilePadding) * std::cos(2 * M_PI * index / tileSides);
    return position;
}

void BoardTile::draw() const
{
    Circle::draw();
    if (hasPiece())
    {
        piece->draw();
    }
}

bool BoardTile::onLeftClick()
{
    if (hovering)
    {
        Game::submit(SelectAction(this));
    }
    return hovering;
}

bool BoardTile::onRightClick()
{
    if (hovering)
    {
        Game::submit(MoveAction(this));
    }
    return hovering;
}

void MenuTile::draw() const
{
    Rectangle::draw();
    if (hasPiece())
    {
        piece->draw();
    }
}

bool MenuTile::onLeftClick()
{
    if (hovering)
    {
        Game::submit(BuildAction(this));
    }
    return hovering;
}

}