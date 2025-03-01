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

    int getGold() const;
    int getFood() const;

    static constexpr size_t maxPlayers = 6u;
    static constexpr size_t minPlayers = 2u;
    static constexpr int startGold = 10;
    static constexpr int startFood = 10;

    static constexpr sf::Color playerColors[maxPlayers] = {
        sf::Color(0, 0, 128, 255),
        sf::Color(128, 0, 0, 255),
        sf::Color(204, 132, 0, 255),
    };

protected:
    std::string name;
    size_t index;
    sf::Color color;
    BoardTile* startTile;
    std::vector<Piece*> pieces;
    std::unordered_map<PieceType, Piece*> menuPieces;
    int gold{startGold};
    int food{startFood};
};

}

#endif