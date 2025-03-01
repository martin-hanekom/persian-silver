#ifndef PERSONAL_SILVER_PIECE_HPP
#define PERSONAL_SILVER_PIECE_HPP

#include <set>
#include <SFML/Graphics.hpp>

namespace silver
{

class Tile;
class BoardTile;
class Player;

enum class PieceType
{
    Man,
    City
};

class PieceCost
{
public:
    constexpr PieceCost(int gold, int food) : gold(gold), food(food)
    {
    }

    int const gold;
    int const food;
};

class Piece
{
public:
    Piece(PieceType type, Player* player);
    ~Piece();

    static Piece* create(PieceType pieceType, Player* player);
    static std::string const& name(PieceType pieceType);

    void draw() const;
    void setTile(Tile* newTile);
    bool isTile(Tile* newTile) const;

    bool isPlayer(Player const& p) const;
    Player* getPlayer();
    Tile* getTile();
    std::string const& getName() const;
    void setSize(float width);

    virtual bool validMove(BoardTile* tile) const = 0;
    virtual void move(BoardTile* tile) = 0;
    virtual void reset() = 0;
    virtual std::set<PieceType> buildable() const = 0;

    static constexpr PieceType pieces[]{PieceType::Man, PieceType::City};
    static constexpr size_t numPieces{2u};

protected:
    PieceType type;
    sf::Sprite sprite;
    Player* player;
    Tile* tile;
};

}

#endif