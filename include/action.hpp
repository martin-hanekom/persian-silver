#ifndef PERSIAN_SILVER_ACTION_HPP
#define PERSIAN_SILVER_ACTION_HPP

#include "tile.hpp"

namespace silver {

enum class ActionType
{
    Select,
    Move,
    Fight,
    Build
};


class Action
{
public:
    Action(ActionType type, Tile* tile);

    bool valid() const;
    Piece* getPiece();

protected:
    ActionType type;
    Tile* const tile;
};

class SelectAction : public Action
{
public:
    SelectAction(Tile* tile);
};

class MoveAction : public Action
{
public:
    MoveAction(Tile* tile);
};

class FightAction : public Action
{
public:
    FightAction(Tile* tile);
};

class BuildAction : public Action
{
public:
    BuildAction(Tile* tile);
};

}

#endif