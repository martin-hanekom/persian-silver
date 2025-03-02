#include "tile.hpp"
#include "player.hpp"
#include "unit.hpp"
#include "asset.hpp"

namespace silver
{

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

Man::Man(Player* player)
    : Unit(PieceType::Man, player)
{
}

std::set<PieceType> Man::buildable() const
{
    return {PieceType::City};
}

PieceType Man::getType() const
{
    return type;
}

}