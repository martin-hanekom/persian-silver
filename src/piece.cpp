#include "piece.hpp"
#include "player.hpp"
#include "tile.hpp"
#include "asset.hpp"
#include "screen.hpp"

Piece::Piece(Player* player, sf::Texture const& texture, Tile* tile)
    : player(player), sprite(texture), tile(tile)
{
    assert(tile != nullptr);
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
    sprite.setColor(player->getColor());
    sprite.setPosition(tile->getPosition());
    tile->setPiece(this);
}

Piece::~Piece()
{
}

void Piece::draw() const
{
    Screen::draw(sprite);
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