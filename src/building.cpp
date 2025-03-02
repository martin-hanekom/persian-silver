#include "building.hpp"

namespace silver
{

City::City(Player* player)
    : Building(PieceType::City, player)
{
}

std::set<PieceType> City::buildable() const
{
    return {PieceType::Man};
}

PieceType City::getType() const
{
    return type;
}

}