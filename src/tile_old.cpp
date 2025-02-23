#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "tile.hpp"
#include "screen.hpp"
#include "util.hpp"

Tile::Tile(sf::Vector2f pos, int depth)
    : Component(depth(depth), color(std::rand() % 2 ? lightGrass : darkGrass)
{
    shape.setOrigin({tileRadius, tileRadius});
    shape.setPosition(pos);
    shape.setFillColor(color);
    shape.setPosition(pos);
    shape.setRotation(sf::radians(tileRotation));
}

void Tile::draw() const
{
    Screen::draw(shape);
}

void Tile::setNeighbor(size_t index, Tile& other)
{
    neighbors[index] = &other;
    other.neighbors[opposite(index)] = this;

    auto leftIndex = (index + tileSides - 1) % tileSides;
    auto rightIndex = (index + 1) % tileSides;
    if (auto left = getNeighbor(leftIndex); left != nullptr)
    {
        auto leftNeighborIndex = (opposite(leftIndex) + tileSides - 1) % tileSides;
        left->neighbors[leftNeighborIndex] = &other;
        other.neighbors[opposite(leftNeighborIndex)] = left;
    }

    if (auto right = getNeighbor(rightIndex); right != nullptr)
    {
        auto rightNeighborIndex = (opposite(rightIndex) + 1) % tileSides;
        right->neighbors[rightNeighborIndex] = &other;
        other.neighbors[opposite(rightNeighborIndex)] = right;
    }
}

Tile* Tile::getNeighbor(size_t index)
{
    return hasNeighbor(index) ? neighbors[index] : nullptr;
}

bool Tile::hasNeighbor(size_t index) const
{
    return neighbors[index] != nullptr;
}

bool Tile::touches(sf::Vector2f point) const
{
    return distance(shape.getPosition(), point) < tileTouch;
}

bool Tile::isSelected() const
{
    return selected;
}

bool Tile::isNeighbor(Tile const* other) const
{
    return std::find(neighbors.cbegin(), neighbors.cend(), other) != neighbors.cend();
}


void Tile::setPosition(sf::Vector2f position)
{
    shape.setPosition(position);
}

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

sf::Vector2f Tile::getNeigborPosition(size_t index) const
{
    auto position = shape.getPosition();
    position.x += 2 * (tileRadius + tilePadding) * std::sin(2 * M_PI * index / tileSides);
    position.y += -2 * (tileRadius + tilePadding) * std::cos(2 * M_PI * index / tileSides);
    return position;
}

void Tile::onHover()
{
    if (!selected)
    {
        shape.setFillColor(Tile::hoverColor);
    }
}

void Tile::offHover()
{
    if (!selected)
    {
        shape.setFillColor(color);
    }
}

void Tile::onSelect()
{
    selected = true;
    shape.setFillColor(Tile::selectColor);
}

void Tile::offSelect()
{
    selected = false;
    shape.setFillColor(color);
}

constexpr size_t Tile::opposite(size_t index)
{
    return (index + tileSides / 2) % tileSides;
}
