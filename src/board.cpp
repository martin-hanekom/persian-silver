#include <algorithm>
#include <deque>
#include <iostream>
#include "board.hpp"
#include "screen.hpp"
#include "util.hpp"

Tile::Tile(sf::Vector2f pos, int depth)
    : depth(depth), shape(tileRadius, tileSides), text(Screen::getFont(), std::to_string(depth)), neighbors({nullptr})
{
    shape.setOrigin({tileRadius, tileRadius});
    shape.setPosition(pos);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(pos);
    shape.setRotation(sf::radians(tileRotation));

    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(pos);
    text.setOrigin(text.getLocalBounds().size / 2.f);
}

void Tile::draw() const
{
    Screen::draw(shape);
    Screen::draw(text);
}

void Tile::setNeighbor(size_t index, Tile& other)
{
    neighbors[index] = &other;
    other.neighbors[opposite(index)] = this;

    auto leftIndex = (index + tileSides - 1) % tileSides;
    auto rightIndex = (index + 1) % tileSides;
    std::cout << leftIndex << ',' << rightIndex << '\n';
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
    return distance(shape.getPosition(), point) < tileRadius;
}

sf::Vector2f Tile::getPosition() const
{
    return shape.getPosition();
}

void Tile::setPosition(sf::Vector2f position)
{
    shape.setPosition(position);
}

sf::Vector2f Tile::getNeigborPosition(size_t index) const
{
    auto position = shape.getPosition();
    std::cout << position.x << ',' << position.y << " [" << index << "] -> ";
    position.x += 2 * (tileRadius + tilePadding) * std::sin(2 * M_PI * index / tileSides);
    position.y += -2 * (tileRadius + tilePadding) * std::cos(2 * M_PI * index / tileSides);
    std::cout << position.x << ',' << position.y << '\n';
    return position;
}

void Tile::clear()
{
    shape.setFillColor(sf::Color::Green);
}

void Tile::onHover()
{
    shape.setFillColor(sf::Color::Red);
    for (auto& neighbor : neighbors)
    {
        if (neighbor != nullptr)
        {
            neighbor->shape.setFillColor(sf::Color::Red);
        }
    }
}

constexpr size_t Tile::opposite(size_t index)
{
    return (index + tileSides / 2) % tileSides;
}

Board::Board(size_t depth)
    : depth(depth)
{
    tiles.reserve(Tile::tileSides * std::pow(2, depth) * 2);
    tiles.emplace_back(sf::Vector2f(0.f, 0.f), 0);
    std::deque<Tile*> tileQueue;
    tileQueue.push_back(&tiles.front());

    while (!tileQueue.empty())
    {
        auto& tile = tileQueue.front();
        for (size_t i = 0; i < 6; ++i)//tile->depth - 1 == depth ? 1 : 6; ++i)
        {
            if (!tile->hasNeighbor(i))
            {
                assert(tiles.capacity() > tiles.size());
                auto& newTile = tiles.emplace_back(tile->getNeigborPosition(i), tile->depth + 1);
                tile->setNeighbor(i, newTile);
                if (newTile.depth < depth)
                {
                    tileQueue.push_back(&newTile);
                }
            }
        }
        std::cout << "Done with tile at " << tile->getPosition().x << ',' << tile->getPosition().y << '\n';
        tileQueue.pop_front();
    }
}

void Board::draw() const
{
    for (auto const& tile : tiles)
    {
        tile.draw();
    }
}

void Board::clear()
{
    for (auto& tile : tiles)
    {
        tile.clear();
    }
}

void Board::onMouseMoved(sf::Vector2f mousePosition)
{
    clear();
    auto it = std::find_if(tiles.begin(), tiles.end(),
        [&mousePosition](Tile const& tile)
        {
            return tile.touches(mousePosition);
        });
    it->onHover();
}