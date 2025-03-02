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
    auto& piece = pieces[0];
    piece->setTile(startTile);
    piece->setEnergy(true);
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
    resources.gold += resources.goldTax;
    resources.food += resources.foodTax;
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

PieceCost const Player::getResources() const
{
    return resources;
}

bool Player::affords(Piece* piece) const
{
    auto const cost = piece->getCost();
    return resources.gold >= cost.gold && resources.food >= cost.food;
}

Piece* Player::buy(PieceType type, Tile* tile)
{
    auto const cost = Piece::cost(type);
    resources.gold -= cost.gold;
    resources.food -= cost.food;
    resources.goldTax += cost.goldTax;
    resources.foodTax += cost.foodTax;
    pieces.push_back(Piece::create(type, this));
    auto& piece = pieces[pieces.size()-1];
    piece->setTile(tile);
    return piece;
}

}