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

protected:
};

class City: public Building
{
public:
    City(Player* player);

    std::set<PieceType> buildable() const override;
    PieceType getType() const;

    static constexpr PieceType type{PieceType::City};  
    static constexpr PieceCost cost{5, 5};
};

}

#endif