#include "building.hpp"

namespace silver
{

bool Building::validMove(BoardTile* newTile) const
{
    return false;
}

void Building::move(BoardTile* newTile)
{
}

void Building::reset()
{
}

City::City(Player* player)
    : Building(PieceType::City, player)
{
}

std::set<PieceType> City::buildable() const
{
    return {PieceType::Man};
}

}