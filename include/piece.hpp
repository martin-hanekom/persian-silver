#ifndef PERSONAL_SILVER_PIECE_HPP
#define PERSONAL_SILVER_PIECE_HPP

#include <SFML/Graphics.hpp>

class Tile;
class Player;

class Piece
{
public:
    Piece(Player* player, sf::Texture const& texture, Tile* tile);
    ~Piece();

    void draw() const;

    Tile* getTile() const;
    virtual bool validMove(Tile* tile) const = 0;
    virtual void move(Tile* tile) = 0;

protected:
    sf::Sprite sprite;
    Player* player;
    Tile* tile;
};

#endif