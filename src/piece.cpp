#include "piece.hpp"
#include "player.hpp"
#include "tile.hpp"
#include "asset.hpp"
#include "screen.hpp"
#include "unit.hpp"
#include "building.hpp"
#include "util.hpp"

namespace silver
{

Piece::Piece(PieceType type, Player* player)
    : type(type), sprite(Asset::getTexture(Piece::name(type))), player(player)
{
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
    sprite.setColor(player->getColor());
}

Piece::~Piece()
{
}

void Piece::draw() const
{
    Screen::draw(sprite);
}

Piece* Piece::create(PieceType pieceType, Player* player)
{
    switch (pieceType)
    {
        case PieceType::Man:
            return new Man(player);
        case PieceType::City:
            return new City(player);
        default:
            return nullptr;
    }
}

std::string const& Piece::name(PieceType type)
{
    static std::unordered_map<PieceType, std::string> const pieceMap = {
        {PieceType::Man, "man"},
        {PieceType::City, "city"}
    };

    return pieceMap.at(type);
}

PieceCost Piece::cost(PieceType type)
{
    static std::unordered_map<PieceType, PieceCost> const pieceMap = {
        {PieceType::Man, Man::cost},
        {PieceType::City, City::cost},
    };

    return pieceMap.at(type);
}

bool Piece::isPlayer(Player const& p) const
{
    return player == &p;
}

Player* Piece::getPlayer()
{
    return player;
}

void Piece::setTile(Tile* newTile)
{
    tile = newTile;
    if (nullptr != tile)
    {
        sprite.setPosition(tile->getPosition());
        setSize(tile->getPieceWidth());
        if (!tile->isPiece(this))
        {
            tile->setPiece(this);
        }
    }
}

bool Piece::isTile(Tile* newTile) const
{
    return tile == newTile;
}

Tile* Piece::getTile()
{
    return tile;
}

std::string const& Piece::getName() const
{
    return Piece::name(type);
}

PieceCost Piece::getCost() const
{
    return Piece::cost(type);
}

void Piece::setSize(float width)
{
    auto newScale = width / sprite.getLocalBounds().size.x;
    sprite.setScale({newScale, newScale});
}

bool Piece::validMove(BoardTile* location) const
{
    return false;
}

void Piece::move(BoardTile* location)
{
}

bool Piece::validBuild(PieceType type, BoardTile* location) const
{
    return energy &&
        nullptr != location &&
        !location->hasPiece() &&
        buildable().count(type) &&
        static_cast<BoardTile*>(tile)->isNeighbor(location);
}

void Piece::build(PieceType type, BoardTile* location)
{
    auto piece = player->buy(type, location);
    setEnergy(false);
    piece->setEnergy(false);
}

void Piece::reset()
{
    setEnergy(true);
}

void Piece::setEnergy(bool up)
{
    energy = up;
    sprite.setColor(opaque(sprite.getColor(), up ? 255u : 128u));
}

bool Piece::hasEnergy() const
{
    return energy;
}

}