#include <algorithm>
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
    if (auto hovering = findHovering(); nullptr != hovering)
    {
        if (hovering->touches(mousePosition))
        {
            return;
        }
        hovering->offHover();
    }

    auto it = std::find_if(tiles.begin(), tiles.end(),
        [&mousePosition](Tile const& tile)
        {
            return tile.touches(mousePosition);
        });

    if (it != tiles.end())
    {
        it->onHover();
    }
}

void Board::onLeftClick()
{
    if (auto selected = findSelected(); nullptr != selected)
    {
        selected->onLeftClick();
    }

    if (auto hovering = findHovering(); nullptr != hovering)
    {
        hovering->onLeftClick();
    }
}

void Board::onRightClick()
{
}

Tile* Board::findHovering()
{
    auto it = std::find_if(tiles.begin(), tiles.end(),
        [](Tile const& tile)
        {
            return tile.isHovering();
        });

    return it == tiles.end() ? nullptr : &*it;
}

Tile* Board::findSelected()
{
    auto it = std::find_if(tiles.begin(), tiles.end(),
        [](Tile const& tile)
        {
            return tile.isSelected();
        });

    return it == tiles.end() ? nullptr : &*it;
}