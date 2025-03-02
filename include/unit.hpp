#ifndef PERSIAN_SILVER_UNIT_HPP
#define PERSIAN_SILVER_UNIT_HPP

#include <set>
#include "piece.hpp"

namespace silver
{

class Unit : public Piece
{
public:
    using Piece::Piece;

    bool validMove(BoardTile* newTile) const override;
    void move(BoardTile* tile) override;
};

class Man : public Unit
{
public:
    Man(Player* player);

    std::set<PieceType> buildable() const override;
    PieceType getType() const override;

    static constexpr PieceType type{PieceType::Man};  
    static constexpr PieceCost cost{1, 1, 0, 0};
};

}

#endif