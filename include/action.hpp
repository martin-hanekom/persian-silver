#ifndef PERSIAN_SILVER_ACTION_HPP
#define PERSIAN_SILVER_ACTION_HPP

#include "tile.hpp"

namespace silver
{

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
    Action(ActionType type);

    virtual bool valid() const = 0;
    virtual Piece* getPiece() = 0;

    ActionType type;
};

class SelectAction : public Action
{
public:
    SelectAction(BoardTile* tile);

    bool valid() const override;
    Piece* getPiece() override;

    BoardTile* tile;
};

class MoveAction : public Action
{
public:
    MoveAction(BoardTile* from, BoardTile* to);

    bool valid() const override;
    Piece* getPiece() override;

    BoardTile* from;
    BoardTile* to;
};

class BuildAction : public Action
{
public:
    BuildAction(MenuTile* tile);

    bool valid() const override;
    Piece* getPiece() override;

    MenuTile* tile;
};

}

#endif