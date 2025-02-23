#include "building.hpp"

bool Building::validMove(Tile* newTile) const
{
    return false;
}

void Building::move(Tile* newTile)
{
}

void Building::reset()
{
}

City::City(Player* player, Tile* tile)
    : Building("city", player, tile)
{
}

std::set<PieceType> City::buildable() const
{
    return {PieceType::Man};
}
