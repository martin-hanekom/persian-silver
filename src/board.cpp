#include <algorithm>
#include <functional>
#include <iostream>
#include <cmath>
#include <deque>
#include "board.hpp"
#include "action.hpp"
#include "game.hpp"

namespace silver
{

Board::Board(size_t depth)
    : depth(depth)
{
    construct();
}

void Board::construct()
{
    tiles.reserve(BoardTile::tileSides * std::pow(2, depth) * 2);
    tiles.clear();
    tiles.emplace_back(sf::Vector2f(0.f, 0.f), 0);
    std::deque<BoardTile*> tileQueue;
    tileQueue.push_back(&tiles.front());

    while (!tileQueue.empty())
    {
        auto& tile = tileQueue.front();
        for (size_t i = 0; i < BoardTile::tileSides; ++i)
        {
            if (!tile->hasNeighbor(i))
            {
                assert(tiles.capacity() > tiles.size());
                auto& newTile = tiles.emplace_back(tile->getNeigborPosition(i), tile->depth + 1);
                tile->setNewNeighbor(i, &newTile);
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

bool Board::onMouseMoved(sf::Vector2f mousePos)
{
    if (nullptr != hovering && hovering->onMouseMoved(mousePos))
    {
        return true;
    }
    hovering = nullptr;

    for (auto& tile : tiles)
    {
        if (tile.onMouseMoved(mousePos))
        {
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

    if (nullptr != hovering && hovering->onLeftClick())
    {
        selected = hovering;
        Game::submit(BoardSelectAction(selected));
    }

    return hovering != nullptr;
}

bool Board::onRightClick()
{
    if (nullptr != selected)
    {
        if (nullptr != hovering && hovering->onRightClick())
        {
            if (nullptr != menuSelected)
            {
                Game::submit(ExpandBuildAction(selected, menuSelected, hovering));
                menuSelected->offSelect();
                menuSelected = nullptr;
            }
            else
            {
                Game::submit(MoveAction(selected, hovering));
            }
        }

        selected->offSelect();
        selected = nullptr;
    }

    return hovering != nullptr;
}

bool Board::touches(sf::Vector2f mousePos) const
{
    return std::any_of(tiles.cbegin(), tiles.cend(), std::bind(BoardTile::touches, std::placeholders::_1, mousePos));
}

BoardTile* Board::center()
{
    return &tiles.front();
}

BoardTile* Board::getStartPos(size_t index)
{
    auto tile = center();
    for (size_t i = 0; i < depth - 2u; ++i)
    {
        tile = tile->neighbors[index];
    }
    return tile;
}

}