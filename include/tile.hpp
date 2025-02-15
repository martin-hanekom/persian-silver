#ifndef PERSIAN_SILVER_TILE_HPP
#define PERSIAN_SILVER_TILE_HPP

#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

class Tile
{
public:
    Tile(sf::Vector2f pos, int depth);
    void draw() const;
    void setNeighbor(size_t index, Tile& neighbor);
    Tile* getNeighbor(size_t index);
    bool hasNeighbor(size_t index) const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getNeigborPosition(size_t index) const;
    void setPosition(sf::Vector2f position);

    void onHover();
    void offHover();
    void onLeftClick();
    void onRightClick();

    bool touches(sf::Vector2f point) const;
    bool isHovering() const;
    bool isSelected() const;

    static constexpr size_t tileSides = 6;
    static constexpr float tileRadius = 100.f;
    static constexpr float tilePadding = -12.f;
    static constexpr float tileRotation = M_PI / tileSides;
    static constexpr sf::Color lightGrass{65, 152, 10};
    static constexpr sf::Color darkGrass{19, 133, 16};

    int const depth;

private:
    static constexpr size_t opposite(size_t index);

    sf::CircleShape shape{tileRadius, tileSides};
    sf::Color color;
    std::array<Tile*, tileSides> neighbors{nullptr};
    bool hovering = false;
    bool selected = false;
};

#endif