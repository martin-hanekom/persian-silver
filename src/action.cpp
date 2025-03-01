#include "action.hpp"

namespace silver
{

Action::Action(ActionType type) : type(type)
{
}

SelectAction::SelectAction(BoardTile* tile) : Action(ActionType::Select), tile(tile)
{
}

bool SelectAction::valid() const
{
    return nullptr != tile && tile->hasPiece();
}

Piece* SelectAction::getPiece()
{
    return nullptr == tile ? nullptr : tile->getPiece();
}

MoveAction::MoveAction(BoardTile* from, BoardTile* to) : Action(ActionType::Move), from(from), to(to)
{
}

bool MoveAction::valid() const
{
    return nullptr != from && nullptr != to && from->hasPiece() && from->getPiece()->validMove(to);
}

Piece* MoveAction::getPiece()
{
    return nullptr == from ? nullptr : from->getPiece();
}

BuildAction::BuildAction(MenuTile* tile) : Action(ActionType::Build), tile(tile)
{
}

bool BuildAction::valid() const
{
    return nullptr != tile && tile->hasPiece();
}

Piece* BuildAction::getPiece()
{
    return nullptr == tile ? nullptr : tile->getPiece();
}

}
