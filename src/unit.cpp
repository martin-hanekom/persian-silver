#include "tile.hpp"
#include "player.hpp"
#include "unit.hpp"
#include "asset.hpp"

namespace silver
{

BuildType Unit::getBuildType() const
{
    return BuildType::Consume;
}

bool Unit::validMove(BoardTile* newTile) const
{
    return energy &&
        nullptr != newTile &&
        !newTile->hasPiece() &&
        static_cast<BoardTile*>(tile)->isNeighbor(newTile);
}

void Unit::move(BoardTile* newTile)
{
    tile->setPiece(nullptr);
    tile = newTile;
    tile->setPiece(this);
    sprite.setPosition(tile->getPosition());
    setEnergy(false);
}

bool Unit::validBuild(PieceType type, BoardTile* location) const
{
    return energy && buildable().count(type);
}

Man::Man(Player* player)
    : Unit(PieceType::Man, player)
{
}

std::set<PieceType> Man::buildable() const
{
    std::set<PieceType> pieces{PieceType::City};
    if (player->hasPiece(PieceType::City))
    {
        pieces.insert(PieceType::Fort);
    }

    return pieces;
}

PieceType Man::getType() const
{
    return type;
}

}