#include "building.hpp"
#include "tile.hpp"
#include "player.hpp"

namespace silver
{

BuildType Building::getBuildType() const
{
    return BuildType::Expand;
}

bool Building::validBuild(PieceType type, BoardTile* location) const
{
    return energy &&
        nullptr != location &&
        !location->hasPiece() &&
        buildable().count(type) &&
        static_cast<BoardTile*>(tile)->isNeighbor(location, buildRange);
}

City::City(Player* player)
    : Building(PieceType::City, player)
{
}

std::set<PieceType> City::buildable() const
{
    std::set<PieceType> pieces{PieceType::Farm, PieceType::Mine, PieceType::Man};
    if (player->hasPiece(PieceType::Farm))
    {
        pieces.insert(PieceType::Windmill);
    }

    if (player->hasPiece(PieceType::Mine))
    {
        pieces.insert(PieceType::Market);
    }

    return pieces;
}

PieceType City::getType() const
{
    return type;
}


Farm::Farm(Player* player)
    : Building(PieceType::Farm, player)
{
}

std::set<PieceType> Farm::buildable() const
{
    return {};
}

PieceType Farm::getType() const
{
    return type;
}

Mine::Mine(Player* player)
    : Building(PieceType::Mine, player)
{
}

std::set<PieceType> Mine::buildable() const
{
    return {};
}

PieceType Mine::getType() const
{
    return type;
}

}