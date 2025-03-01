#include "tile.hpp"
#include "player.hpp"
#include "unit.hpp"
#include "asset.hpp"
#include "util.hpp"

namespace silver
{

bool Unit::validMove(BoardTile* newTile) const
{
    return energy && nullptr != newTile && !newTile->hasPiece() && static_cast<BoardTile*>(tile)->isNeighbor(newTile);
}

void Unit::move(BoardTile* newTile)
{
    tile->setPiece(nullptr);
    tile = newTile;
    tile->setPiece(this);
    sprite.setPosition(tile->getPosition());

    energy = false;
    sprite.setColor(opaque(sprite.getColor(), 128u));
}

void Unit::reset()
{
    if (!energy)
    {
        sprite.setColor(opaque(sprite.getColor(), 255u));
    }
    energy = true;
}

Man::Man(Player* player)
    : Unit(PieceType::Man, player)
{
}

std::set<PieceType> Man::buildable() const
{
    return {PieceType::City};
}

}