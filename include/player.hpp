#ifndef PERSONAL_SILVER_PLAYER_HPP
#define PERSONAL_SILVER_PLAYER_HPP

#include <vector>
#include <unordered_map>
#include "piece.hpp"
#include "tile.hpp"

namespace silver
{

class Player
{
public:
    Player(std::string const& name, size_t index, BoardTile* startTile);
    ~Player();

    void draw() const;
    void reset();
    sf::Color const& getColor() const;
    std::string const& getName() const;
    Piece* getMenuPiece(PieceType pieceType);

    PieceCost const getResources() const;
    bool affords(Piece* piece) const;
    Piece* buy(PieceType type, Tile* tile);
    void expand(PieceType type, Piece* builder, BoardTile* location);
    void consume(PieceType type, Piece* builder); 
    bool hasPiece(PieceType type) const;

    static constexpr size_t maxPlayers = 6u;
    static constexpr size_t minPlayers = 2u;
    static constexpr int startGold = 20;
    static constexpr int startFood = 20;
    static constexpr size_t maxPieces = 255u;

    static constexpr sf::Color playerColors[maxPlayers] = {
        sf::Color(0, 0, 128, 255),
        sf::Color(128, 0, 0, 255),
        sf::Color(57, 170, 170)
    };

protected:
    Piece* add(PieceType type, Tile* tile);
    void remove(Piece* piece);

    std::string name;
    size_t index;
    sf::Color color;
    BoardTile* startTile;
    std::vector<Piece*> pieces;
    std::unordered_map<PieceType, Piece*> menuPieces;
    PieceCost resources{startGold, startFood, 0, 0};
};

}

#endif