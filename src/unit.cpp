#include "tile.hpp"
#include "player.hpp"
#include "unit.hpp"
#include "asset.hpp"

bool Unit::validMove(Tile* newTile) const
{
    return nullptr != newTile && !newTile->hasPiece() && tile->isNeighbor(newTile);
}

void Unit::move(Tile* newTile)
{
    tile->setPiece(nullptr);
    tile = newTile;
    tile->setPiece(this);
    sprite.setPosition(tile->getPosition());
}

Man::Man(Player* player, Tile* tile)
    : Unit(player, Asset::getTexture("man"), tile)
{
}