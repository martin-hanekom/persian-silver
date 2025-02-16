#include <algorithm>
#include <functional>
#include "player.hpp"
#include "unit.hpp"

Player::Player(std::string const& name, size_t index, Tile* startTile)
    : name(name), index(index), color(playerColors[index]), startTile(startTile)
{
    pieces.push_back(new Man(this, startTile));
    /*
    for (size_t i = 0; i < 10; ++i)
    {
        pieces.emplace_back(name, color, startTile);
    }
        */
}

Player::~Player()
{
    std::for_each(pieces.begin(), pieces.end(), std::default_delete<Piece>());
}

void Player::draw() const
{
    std::for_each(pieces.cbegin(), pieces.cend(), std::bind(&Piece::draw, std::placeholders::_1));
}

sf::Color const& Player::getColor() const
{
    return color;
}