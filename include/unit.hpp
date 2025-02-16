#ifndef PERSIAN_SILVER_UNIT_HPP
#define PERSIAN_SILVER_UNIT_HPP

#include "piece.hpp"

class Unit: public Piece
{
public:
    using Piece::Piece;

    bool validMove(Tile* newTile) const override;
    void move(Tile* tile) override;

};

class Man: public Unit
{
public:
    Man(Player* player, Tile* tile);
};

#endif