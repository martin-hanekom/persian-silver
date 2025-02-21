#ifndef PERSIAN_SILVER_ACTION_HPP
#define PERSIAN_SILVER_ACTION_HPP

#include <memory>
#include "tile.hpp"

enum class ActionType
{
    Move,
    Fight,
    Build
};

class Action
{
public:
    virtual bool valid() const = 0;
    virtual Piece* getPiece() = 0;
};

class MoveAction: public Action
{
public:
    MoveAction(Tile* from, Tile* to);
    bool valid() const override;
    Piece* getPiece() override;

    Tile* const from;
    Tile* const to;
};

class FightAction: public Action
{

};

class BuildAction: public Action
{

};

#endif