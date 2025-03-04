#ifndef PERSIAN_SILVER_ACTION_HPP
#define PERSIAN_SILVER_ACTION_HPP

#include "tile.hpp"
#include "player.hpp"

namespace silver
{

enum class ActionType
{
    BoardSelect,
    MenuSelect,
    Move,
    Fight,
    ExpandBuild,
    ConsumeBuild,
};

class Action
{
public:
    Action(ActionType type);

    virtual bool valid(Player const& player) const = 0;
    virtual Piece* getPiece() = 0;

    ActionType type;
};

class BoardSelectAction : public Action
{
public:
    BoardSelectAction(BoardTile* tile);

    bool valid(Player const& player) const override;
    Piece* getPiece() override;

    BoardTile* tile;
};

class MenuSelectAction: public Action
{
public:
    MenuSelectAction(MenuTile* tile);

    bool valid(Player const& player) const override;
    Piece* getPiece() override;

    MenuTile* tile;
};

class MoveAction : public Action
{
public:
    MoveAction(BoardTile* from, BoardTile* to);

    bool valid(Player const& player) const override;
    Piece* getPiece() override;

    BoardTile* from;
    BoardTile* to;
};

class ExpandBuildAction : public Action
{
public:
    ExpandBuildAction(BoardTile* builder, MenuTile* menuTile, BoardTile* location);

    bool valid(Player const& player) const override;
    Piece* getPiece() override;
    PieceType getPieceType() const;

    BoardTile* builder;
    MenuTile* menuItem;
    BoardTile* location;
};

class ConsumeBuildAction : public Action
{
public:
    ConsumeBuildAction(BoardTile* builder, MenuTile* menuTile);

    bool valid(Player const& player) const override;
    Piece* getPiece() override;
    PieceType getPieceType() const;

    BoardTile* builder;
    MenuTile* menuItem;
};

}

#endif