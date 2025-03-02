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
    static PieceCost cost(PieceType type);

    void draw() const;
    void setTile(Tile* newTile);
    bool isTile(Tile* newTile) const;

    bool isPlayer(Player const& p) const;
    Player* getPlayer();
    Tile* getTile();
    std::string const& getName() const;
    void setSize(float width);
    virtual PieceType getType() const = 0;
    PieceCost getCost() const;

    virtual bool validMove(BoardTile* location) const;
    virtual void move(BoardTile* location);
    bool validBuild(PieceType type, BoardTile* location) const;
    void build(PieceType type, BoardTile* location);
    virtual void reset();
    void setEnergy(bool up);
    bool hasEnergy() const;
    virtual std::set<PieceType> buildable() const = 0;

    static constexpr PieceType pieces[]{PieceType::Man, PieceType::City};
    static constexpr size_t numPieces{2u};

protected:
    PieceType type;
    sf::Sprite sprite;
    Player* player;
    Tile* tile;
    bool energy = true;
};

}

#endif