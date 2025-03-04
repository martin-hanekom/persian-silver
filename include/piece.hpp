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
    Soldier,
    Spearman,
    Archer,
    Knight,
    HorseArcher,
    Cannon,
    City,
    Farm,
    Mine,
    Windmill,
    Market,
    Fort,
    Stables,
    Blacksmith,
};

enum class BuildType
{
    Expand,
    Consume,
};

class PieceCost
{
public:
    constexpr PieceCost(int gold, int food, int goldTax, int foodTax) :
        gold(gold), food(food), goldTax(goldTax), foodTax(foodTax)
    {
    }

    int gold;
    int food;
    int goldTax;
    int foodTax;

    std::string goldText() const;
    std::string foodText() const;
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
    virtual BuildType getBuildType() const = 0;
    PieceCost getCost() const;

    virtual bool validMove(BoardTile* location) const;
    virtual void move(BoardTile* location);
    virtual bool validBuild(PieceType type, BoardTile* location = nullptr) const = 0;
    virtual void reset();
    void setEnergy(bool up);
    bool hasEnergy() const;
    virtual std::set<PieceType> buildable() const = 0;

    static constexpr PieceType pieces[]{
        PieceType::Man,
        PieceType::Soldier,
        PieceType::Spearman,
        PieceType::Archer,
        PieceType::Knight,
        PieceType::HorseArcher,
        PieceType::Cannon,
        PieceType::City,
        PieceType::Farm,
        PieceType::Mine,
        PieceType::Windmill,
        PieceType::Market,
        PieceType::Fort,
        PieceType::Stables,
        PieceType::Blacksmith,
    };
    static constexpr size_t numPieces{15u};

protected:
    PieceType type;
    sf::Sprite sprite;
    Player* player = nullptr;
    Tile* tile = nullptr;
    bool energy = true;
};

}

#endif