#ifndef PERSIAN_SILVER_BUILDING_HPP
#define PERSIAN_SILVER_BUILDING_HPP

#include "piece.hpp"

class Building: public Piece
{
public:
    using Piece::Piece;

    bool validMove(Tile* newTile) const override;
    void move(Tile* tile) override;
    void reset() override;

private:
};

#endif