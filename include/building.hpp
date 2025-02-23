#ifndef PERSIAN_SILVER_BUILDING_HPP
#define PERSIAN_SILVER_BUILDING_HPP

#include <set>
#include "piece.hpp"

class Building: public Piece
{
public:
    using Piece::Piece;

    bool validMove(Tile* newTile) const override;
    void move(Tile* tile) override;
    void reset() override;

protected:
};

class City: public Building
{
public:
    City(Player* player, Tile* tile);

    std::set<PieceType> buildable() const override;
};

#endif