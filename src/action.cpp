#include "action.hpp"

MoveAction::MoveAction(Tile* from, Tile* to): from(from), to(to)
{
}

bool MoveAction::valid() const
{
    if (nullptr == from || nullptr == to)
    {
        return false;
    }

    auto piece = from->getPiece();
    return nullptr != piece && piece->validMove(to);
}

Piece* MoveAction::getPiece()
{
    if (nullptr == from)
    {
        return nullptr;
    }

    return from->getPiece();
}
