#include <algorithm>
#include <functional>
#include "player.hpp"
#include "unit.hpp"

namespace silver
{

Player::Player(std::string const& name, size_t index, BoardTile* startTile)
    : name(name), index(index), color(playerColors[index]), startTile(startTile)
{
    for (auto i = 0u; i < Piece::numPieces; ++i)
    {
        auto& pieceType = Piece::pieces[i];
        menuPieces[pieceType] = Piece::create(pieceType, this);
    }

    pieces.push_back(Piece::create(PieceType::Man, this));
    pieces[0]->setTile(startTile);
}

Player::~Player()
{
    for (auto& piece : pieces)
    {
        delete piece;
    }

    for (auto& [pieceType, piece] : menuPieces)
    {
        delete piece;
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

Piece* Player::getMenuPiece(PieceType pieceType)
{
    return menuPieces[pieceType];
}

int Player::getGold() const
{
    return gold;
}

int Player::getFood() const
{
    return food;
}

}