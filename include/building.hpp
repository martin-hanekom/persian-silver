#ifndef PERSIAN_SILVER_BUILDING_HPP
#define PERSIAN_SILVER_BUILDING_HPP

#include <set>
#include "piece.hpp"

namespace silver
{

class Building : public Piece
{
public:
    using Piece::Piece;

    BuildType getBuildType() const override;
    bool validBuild(PieceType type, BoardTile* location) const override;
    static constexpr size_t buildRange{2u};

protected:
};

class City : public Building
{
public:
    City(Player* player);

    std::set<PieceType> buildable() const override;
    PieceType getType() const;

    static constexpr PieceType type{PieceType::City};  
    static constexpr PieceCost cost{10, 0, 1, 1};
};

class Farm : public Building
{
public:
    Farm(Player* player);

    std::set<PieceType> buildable() const override;
    PieceType getType() const;

    static constexpr PieceType type{PieceType::Farm};  
    static constexpr PieceCost cost{3, 0, 4, 0};
};

class Mine : public Building
{
public:
    Mine(Player* player);

    std::set<PieceType> buildable() const override;
    PieceType getType() const;

    static constexpr PieceType type{PieceType::Mine};  
    static constexpr PieceCost cost{5, 0, 0, 2};
};

}

#endif