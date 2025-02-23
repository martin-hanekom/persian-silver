#ifndef PERSIAN_SILVER_TILE_HPP
#define PERSIAN_SILVER_TILE_HPP

#include <SFML/Graphics.hpp>
#include "piece.hpp"
#include "ui.hpp"

namespace silver
{

class Tile
{
public:
    void setPiece(Piece* piece);
    Piece* getPiece();
    bool hasPiece() const;

protected:
    Piece* piece = nullptr;
};

class BoardTile: public Circle, Tile
{
public:
    BoardTile(sf::Vector2f pos, int depth);

    void setNewNeighbor(size_t index, BoardTile* other);
    void setNeighbor(size_t index, BoardTile* other);
    BoardTile* getNeighbor(size_t index);
    bool hasNeighbor(size_t index) const;
    sf::Vector2f getNeigborPosition(size_t index) const;

    void draw() const override;
    bool onLeftClick() override;
    bool onRightClick() override;

    static constexpr size_t tileSides = 6;
    static constexpr float tileRadius = 150.f;
    static constexpr float tilePadding = -18.f;
    static constexpr float tileRotation = M_PI / tileSides;
    static constexpr sf::Color lightGrass{65, 152, 10};
    static constexpr sf::Color darkGrass{19, 133, 16};
    static constexpr sf::Color defaultHoverColor{sf::Color::Magenta};
    static constexpr sf::Color selectColor{sf::Color::Yellow};

protected:
    static constexpr size_t opposite(size_t index);

    int depth;
    std::array<BoardTile*, tileSides> neighbors{nullptr};
};

class MenuTile: public Rectangle, Tile
{
public:
    MenuTile(sf::Vector2f pos);

    void draw() const override;
    bool onLeftClick() override;

    static constexpr float tileSize = 100.f;
    static constexpr sf::Color tileColor{80, 92, 95};
    static constexpr sf::Color defaultHoverColor{85, 97, 100};
};

}

#endif