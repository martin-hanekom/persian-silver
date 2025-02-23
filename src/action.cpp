#include "action.hpp"

namespace silver
{

Action::Action(ActionType type, Tile* tile) : type(type), tile(tile)
{
}

bool Action::valid() const
{
    return nullptr != tile && tile->hasPiece();
}

Piece* Action::getPiece()
{
    return nullptr == tile ? nullptr : tile->getPiece();
}

SelectAction::SelectAction(Tile* tile) : Action(ActionType::Select, tile)
{
}

MoveAction::MoveAction(Tile* tile) : Action(ActionType::Move, tile)
{
}

FightAction::FightAction(Tile* tile) : Action(ActionType::Fight, tile)
{
}

BuildAction::BuildAction(Tile* tile) : Action(ActionType::Build, tile)
{
}

}
