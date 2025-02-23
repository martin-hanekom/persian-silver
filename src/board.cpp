#include <algorithm>
#include <iostream>
#include <cmath>
#include <deque>
#include "board.hpp"
#include "action.hpp"
#include "game.hpp"

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

bool Board::onMouseMoved(sf::Vector2f mousePosition)
{
    if (hovering != nullptr)
    {
        if (hovering->touches(mousePosition))
        {
            return true;
        }

        hovering->offHover();
        for (auto tile : hovering->neighbors)
        {
            if (tile != nullptr && tile->touches(mousePosition))
            {
                tile->onHover();
                hovering = tile;
                return true;
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
            return true;
        }
    }

    return false;
}

bool Board::onLeftClick()
{
    if (nullptr != selected)
    {
        selected->offSelect();
        selected = nullptr;
    }

    if (nullptr != hovering)
    {
        selected = hovering;
        selected->onSelect();
    }

    Game::submit(SelectAction(selected));
    return selected != nullptr;
}

bool Board::onRightClick()
{
    if (nullptr == hovering || nullptr == selected)
    {
        return false;
    }

    Game::submit(MoveAction(selected, hovering));
    selected->offSelect();
    selected = nullptr;
    return true;
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