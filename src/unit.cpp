#include "tile.hpp"
#include "player.hpp"
#include "unit.hpp"
#include "asset.hpp"
#include "util.hpp"

bool Unit::validMove(Tile* newTile) const
{
    return energy && nullptr != newTile && !newTile->hasPiece() && tile->isNeighbor(newTile);
}

void Unit::move(Tile* newTile)
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

Man::Man(Player* player, Tile* tile)
    : Unit("man", player, tile)
{
}

std::set<PieceType> Man::buildable() const
{
    return {PieceType::City};
}