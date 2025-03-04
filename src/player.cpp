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

    pieces.reserve(maxPieces);
    add(PieceType::Man, startTile);
}

Player::~Player()
{
    for (auto piece : pieces)
    {
        if (nullptr != piece)
        {
            delete piece;
        }
    }

    for (auto [pieceType, piece] : menuPieces)
    {
        delete piece;
    }
}

void Player::draw() const
{
    for (auto const piece : pieces)
    {
        if (nullptr != piece)
        {
            piece->draw();
        }
    }
}

void Player::reset()
{
    for (auto& piece : pieces)
    {
        if (nullptr != piece)
        {
            piece->reset();
        }
    }
    resources.gold += resources.goldTax;
    resources.food += resources.foodTax;
}

bool Player::hasPiece(PieceType type) const
{
    return std::any_of(pieces.cbegin(), pieces.cend(), [type](auto const* const piece)
        {
            return nullptr != piece && piece->getType() == type;
        });
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

Piece* Player::add(PieceType type, Tile* tile)
{
    auto piece = Piece::create(PieceType::Man, this);
    piece->setTile(tile);

    if (auto it = std::find(pieces.begin(), pieces.end(), nullptr); it != pieces.end())
    {
        *it = piece;
    }
    else
    {
        pieces.push_back(piece);
    }

    return piece;
}

void Player::remove(Piece* piece)
{
    if (nullptr == piece)
    {
        return;
    }

    piece->setTile(nullptr);
    delete piece;

    if (auto it = std::find(pieces.begin(), pieces.end(), piece); it != pieces.end())
    {
        *it = nullptr;
    }
}

void Player::expand(PieceType type, Piece* builder, BoardTile* location)
{
    auto piece = buy(type, location);
    builder->setEnergy(false);
    piece->setEnergy(false);
}

void Player::consume(PieceType type, Piece* builder)
{
    auto location = builder->getTile();
    remove(builder);
    auto piece = buy(type, location);
    piece->setEnergy(false);
}

}