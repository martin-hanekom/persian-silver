#ifndef PERSIAN_SILVER_BUILDING_HPP
#define PERSIAN_SILVER_BUILDING_HPP

#include <set>
#include "piece.hpp"

namespace silver
{

class Building: public Piece
{
public:
    using Piece::Piece;

    bool validMove(BoardTile* newTile) const override;
    void move(BoardTile* tile) override;
    void reset() override;

protected:
};

class City: public Building
{
public:
    City(Player* player);

    std::set<PieceType> buildable() const override;
    PieceCost const& getCost() const;

    static constexpr PieceType type{PieceType::City};  
    static constexpr PieceCost cost{5, 5};
};

}

#endif