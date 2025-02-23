#ifndef PERSONAL_SILVER_PIECE_HPP
#define PERSONAL_SILVER_PIECE_HPP

#include <set>
#include <SFML/Graphics.hpp>

class Tile;
class Player;

enum class PieceType
{
    Man,
    City
};

class Piece
{
public:
    Piece(std::string const& name, Player* player, Tile* tile);
    ~Piece();

    static Piece* create(PieceType pieceType, Player* player, Tile* tile);
    void draw() const;

    bool isPlayer(Player const& p) const;
    Player* getPlayer();
    Tile* getTile();
    std::string const& getName() const;

    virtual bool validMove(Tile* tile) const = 0;
    virtual void move(Tile* tile) = 0;
    virtual void reset() = 0;
    virtual std::set<PieceType> buildable() const = 0;

protected:
    std::string name;
    sf::Sprite sprite;
    Player* player;
    Tile* tile;
};

#endif