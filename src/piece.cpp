#include "piece.hpp"
#include "player.hpp"
#include "tile.hpp"
#include "asset.hpp"
#include "screen.hpp"
#include "unit.hpp"
#include "building.hpp"

Piece::Piece(std::string const& name, Player* player, Tile* tile)
    : name(name), sprite(Asset::getTexture(name)), player(player), tile(tile)
{
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
    sprite.setColor(player->getColor());
    if (nullptr != tile)
    {
        sprite.setPosition(tile->getPosition());
        tile->setPiece(this);
    }
}

Piece::~Piece()
{
}

void Piece::draw() const
{
    Screen::draw(sprite);
}

Piece* Piece::create(PieceType pieceType, Player* player, Tile* tile)
{
    switch (pieceType)
    {
        case PieceType::Man:
            return new Man(player, tile);
        case PieceType::City:
            return new City(player, tile);
        default:
            return nullptr;
    }
}

bool Piece::isPlayer(Player const& p) const
{
    return player == &p;
}

Player* Piece::getPlayer()
{
    return player;
}

Tile* Piece::getTile()
{
    return tile;
}

std::string const& Piece::getName() const
{
    return name;
}