#ifndef PERSONAL_SILVER_PLAYER_HPP
#define PERSONAL_SILVER_PLAYER_HPP

#include <vector>
#include "piece.hpp"

class Player
{
public:
    Player(std::string const& name, size_t index, Tile* startTile);
    ~Player();

    void draw() const;
    void reset();
    sf::Color const& getColor() const;
    std::string const& getName() const;

    static constexpr size_t maxPlayers = 6u;
    static constexpr size_t minPlayers = 2u;

    static constexpr sf::Color playerColors[maxPlayers] = {
        sf::Color(0, 0, 128, 255),
        sf::Color(128, 0, 0, 255),
        sf::Color(204, 132, 0, 255),
    };

private:
    std::string name;
    size_t index;
    sf::Color color;
    Tile* startTile;
    std::vector<Piece*> pieces;
};

#endif