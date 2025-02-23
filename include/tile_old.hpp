#ifndef PERSIAN_SILVER_TILE_HPP
#define PERSIAN_SILVER_TILE_HPP

#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "piece.hpp"
#include "ui.hpp"

class Tile: public Component
{
public:
    Tile(sf::Vector2f pos, int depth);
    void draw() const;
    void setNeighbor(size_t index, Tile& neighbor);
    Tile* getNeighbor(size_t index);
    bool hasNeighbor(size_t index) const;
    sf::Vector2f getNeigborPosition(size_t index) const;
    void setPosition(sf::Vector2f position);

    void setPiece(Piece* piece);
    Piece* getPiece();
    bool hasPiece() const;

    void onHover();
    void offHover();
    void onSelect();
    void offSelect();

    bool touches(sf::Vector2f point) const;
    bool isSelected() const;
    bool isNeighbor(Tile const* other) const;

    static constexpr size_t tileSides = 6;
    static constexpr float tileRadius = 150.f;
    static constexpr float tilePadding = -18.f;
    static constexpr float tileTouch = tileRadius + tilePadding / 2.f;
    static constexpr float tileRotation = M_PI / tileSides;
    static constexpr sf::Color lightGrass{65, 152, 10};
    static constexpr sf::Color darkGrass{19, 133, 16};
    static constexpr sf::Color hoverColor{sf::Color::Magenta};
    static constexpr sf::Color selectColor{sf::Color::Yellow};

    int const depth;
    std::array<Tile*, tileSides> neighbors{nullptr};

private:
    static constexpr size_t opposite(size_t index);

    sf::CircleShape shape{tileRadius, tileSides};
    sf::Color color;
    Piece* piece;
    bool selected = false;
};

#endif