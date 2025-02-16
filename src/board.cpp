#include <algorithm>
#include <iostream>
#include <cmath>
#include <deque>
#include "board.hpp"

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

void Board::onMouseMoved(sf::Vector2f mousePosition)
{
    if (hovering != nullptr)
    {
        if (hovering->touches(mousePosition))
        {
            return;
        }

        hovering->offHover();
        for (auto tile : hovering->neighbors)
        {
            if (tile != nullptr && tile->touches(mousePosition))
            {
                tile->onHover();
                hovering = tile;
                return;
            }
        }
        hovering = nullptr;
    }

    for (auto& tile : tiles)
    {
        if (tile.touches(mousePosition))
        {
            tile.onHover();
            hovering = &tile;
            return;
        }
    }
}

void Board::onLeftClick()
{
    if (nullptr != hovering)
    {
        if (nullptr != selected)
        {
            auto piece = selected->getPiece();
            if (piece != nullptr && piece->validMove(hovering))
            {
                piece->move(hovering);
            }
            selected->offSelect();
            selected = nullptr;
        }
        else
        {
            selected = hovering;
            selected->onSelect();
        }
    }
    else
    {
        if (selected != nullptr)
        {
            selected->offSelect();
            selected = nullptr;
        }
    }
}

void Board::onRightClick()
{
}

Tile* Board::center()
{
    return &tiles.front();
}

Tile* Board::getStartPos(size_t index)
{
    Tile* tile = center();
    for (size_t i = 0; i < depth - 2u; ++i)
    {
        tile = tile->neighbors[index];
    }
    return tile;
}