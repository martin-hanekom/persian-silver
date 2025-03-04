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

ExpandBuildAction::ExpandBuildAction(BoardTile* builder, MenuTile* menuItem, BoardTile* location) :
    Action(ActionType::ExpandBuild), builder(builder), menuItem(menuItem), location(location)
{
}

bool ExpandBuildAction::valid(Player const& player) const
{
    auto builderPiece = nullptr != builder ? builder->getPiece() : nullptr;
    auto piece = nullptr != menuItem ? menuItem->getPiece() : nullptr;
    return builderPiece != nullptr &&
        piece != nullptr &&
        builderPiece->isPlayer(player) &&
        builderPiece->validBuild(piece->getType(), location) &&
        player.affords(piece);
}

Piece* ExpandBuildAction::getPiece()
{
    return nullptr == builder ? nullptr : builder->getPiece();
}

PieceType ExpandBuildAction::getPieceType() const
{
    return menuItem->getPiece()->getType();
}

ConsumeBuildAction::ConsumeBuildAction(BoardTile* builder, MenuTile* menuItem) :
    Action(ActionType::ConsumeBuild), builder(builder), menuItem(menuItem)
{
}

bool ConsumeBuildAction::valid(Player const& player) const
{
    auto builderPiece = nullptr != builder ? builder->getPiece() : nullptr;
    auto piece = nullptr != menuItem ? menuItem->getPiece() : nullptr;
    return builderPiece != nullptr &&
        piece != nullptr &&
        builderPiece->isPlayer(player) &&
        builderPiece->validBuild(piece->getType()) &&
        player.affords(piece);
}

Piece* ConsumeBuildAction::getPiece()
{
    return nullptr == builder ? nullptr : builder->getPiece();
}

PieceType ConsumeBuildAction::getPieceType() const
{
    return menuItem->getPiece()->getType();
}

}
