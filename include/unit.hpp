#ifndef PERSIAN_SILVER_UNIT_HPP
#define PERSIAN_SILVER_UNIT_HPP

#include <set>
#include "piece.hpp"

class Unit: public Piece
{
public:
    using Piece::Piece;

    bool validMove(Tile* newTile) const override;
    void move(Tile* tile) override;
    void reset() override;

protected:
    bool energy = true;
};

class Man: public Unit
{
public:
    Man(Player* player, Tile* tile);

    std::set<PieceType> buildable() const override;

    static constexpr PieceType type{PieceType::Man};  
};

#endif