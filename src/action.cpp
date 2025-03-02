#include "action.hpp"

namespace silver
{

Action::Action(ActionType type) : type(type)
{
}

BoardSelectAction::BoardSelectAction(BoardTile* tile) : Action(ActionType::BoardSelect), tile(tile)
{
}

bool BoardSelectAction::valid(Player const& player) const
{
    auto piece = tile->getPiece();
    return nullptr != piece &&
        piece->hasEnergy() &&
        piece->isPlayer(player);
}

Piece* BoardSelectAction::getPiece()
{
    return nullptr == tile ? nullptr : tile->getPiece();
}

MenuSelectAction::MenuSelectAction(MenuTile* tile) : Action(ActionType::MenuSelect), tile(tile)
{
}

bool MenuSelectAction::valid(Player const& player) const
{
    return nullptr != tile &&
        tile->hasPiece();
}

Piece* MenuSelectAction::getPiece()
{
    return nullptr == tile ? nullptr : tile->getPiece();
}

MoveAction::MoveAction(BoardTile* from, BoardTile* to) :
    Action(ActionType::Move), from(from), to(to)
{
}

bool MoveAction::valid(Player const& player) const
{
    auto piece = from->getPiece();
    return nullptr != piece &&
        piece->isPlayer(player) &&
        piece->validMove(to);
}

Piece* MoveAction::getPiece()
{
    return nullptr == from ? nullptr : from->getPiece();
}

BuildAction::BuildAction(BoardTile* builder, MenuTile* menuItem, BoardTile* location) :
    Action(ActionType::Build), builder(builder), menuItem(menuItem), location(location)
{
}

bool BuildAction::valid(Player const& player) const
{
    auto piece = nullptr != builder ? builder->getPiece() : nullptr;
    return piece != nullptr &&
        menuItem->hasPiece() &&
        piece->isPlayer(player) &&
        piece->validBuild(menuItem->getPiece()->getType(), location) &&
        player.affords(piece);
}

Piece* BuildAction::getPiece()
{
    return nullptr == builder ? nullptr : builder->getPiece();
}

PieceType BuildAction::getPieceType() const
{
    return menuItem->getPiece()->getType();
}

}
