#include <algorithm>
#include <functional>
#include "player.hpp"
#include "unit.hpp"

Player::Player(std::string const& name, size_t index, Tile* startTile)
    : name(name), index(index), color(playerColors[index]), startTile(startTile)
{
    pieces.push_back(Piece::create(PieceType::Man, this, startTile));
    /*
    for (size_t i = 0; i < 10; ++i)
    {
        pieces.emplace_back(name, color, startTile);
    }
        */
}

Player::~Player()
{
    for (auto i = 0u; i < pieces.size(); ++i)
    {
        delete pieces[i];
    }
}

void Player::draw() const
{
    std::for_each(pieces.cbegin(), pieces.cend(), std::bind(&Piece::draw, std::placeholders::_1));
}

void Player::reset()
{
    for (auto& piece : pieces)
    {
        piece->reset();
    }
}

sf::Color const& Player::getColor() const
{
    return color;
}

std::string const& Player::getName() const
{
    return name;
}