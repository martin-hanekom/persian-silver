#ifndef PERSIAN_SILVER_TILE_HPP
#define PERSIAN_SILVER_TILE_HPP

#include <cmath>
#include <SFML/Graphics.hpp>
#include "piece.hpp"
#include "ui.hpp"
#include "resource.hpp"
#include "asset.hpp"

namespace silver
{

class Tile
{
public:
    virtual void setPiece(Piece* piece);
    Piece* getPiece();
    bool hasPiece() const;
    bool isPiece(Piece* piece) const;

    virtual sf::Vector2f getPosition() const = 0;
    virtual float getPieceWidth() const = 0;

    static constexpr float pieceFillRatio = 0.7f;

protected:
    Piece* piece = nullptr;
};

class BoardTile: public Tile, public Circle
{
public:
    BoardTile(sf::Vector2f pos, int depth);

    void setNewNeighbor(size_t index, BoardTile* other);
    void setNeighbor(size_t index, BoardTile* other);
    BoardTile* getNeighbor(size_t index);
    bool hasNeighbor(size_t index) const;
    bool isNeighbor(BoardTile const* other) const;
    sf::Vector2f getNeigborPosition(size_t index) const;

    sf::Vector2f getPosition() const override;
    float getPieceWidth() const override;
    void draw() const override;
    bool onLeftClick() override;

    void onHover();
    void offHover();
    void onSelect();
    void offSelect();

    static constexpr size_t tileSides = 6;
    static constexpr float tileRadius = 150.f;
    static constexpr float tilePadding = -18.f;
    static constexpr float tileRotation = M_PI / tileSides;
    static constexpr sf::Color lightGrass{65, 152, 10};
    static constexpr sf::Color darkGrass{19, 133, 16};
    static constexpr sf::Color defaultHoverColor{19, 109, 21};
    static constexpr sf::Color selectColor{sf::Color::Yellow};

    int depth;
    std::array<BoardTile*, tileSides> neighbors{nullptr};

protected:
    static constexpr size_t opposite(size_t index);

    bool selected = false;
};

class Glyph : public Circle
{
public:
    Glyph(sf::Vector2f pos, float radius);
    ~Glyph();

    void setPosition(sf::Vector2f pos) override;
    sf::Vector2f getPosition() const;
    float getResourceWidth() const;
    void draw() const override;
    bool isResource(Resource* resource) const;
    bool hasResource() const;
    void setResource(Resource* newResource);

    static constexpr size_t tileSides = 30;
    static constexpr sf::Color tileColor{80, 92, 95};
    static constexpr float resourceFillRatio = 0.95f;

protected:
    Resource* resource = nullptr;
};

class MenuTile: public Tile, public Rectangle
{
public:
    MenuTile(sf::Vector2f pos = {0.f, 0.f});

    void setPiece(Piece* piece) override;
    sf::Vector2f getPosition() const override;
    float getPieceWidth() const override;
    void draw() const override;
    bool onLeftClick() override;
    void setPosition(sf::Vector2f pos) override;

    void onHover();
    void offHover();
    void onSelect();
    void offSelect();

    static constexpr float tileSize = 90.f;
    static constexpr float tileHalfSize = tileSize / 2.f;
    static constexpr sf::Color tileColor{80, 92, 95};
    static constexpr sf::Color defaultHoverColor{85, 97, 100};
    static constexpr sf::Color selectColor{sf::Color::Magenta};
    static constexpr float glyphRadius = 20.f;
    static constexpr float glyphDiameter = 20.f;
    static constexpr sf::Vector2f padding{10.f, 2.f};

protected:
    Glyph goldTile;
    Glyph foodTile;
    sf::Text goldBuild{Asset::getFont(), ""};
    sf::Text goldTax{Asset::getFont(), ""};
    sf::Text foodBuild{Asset::getFont(), ""};
    sf::Text foodTax{Asset::getFont(), ""};
    bool selected = false;
};

}

#endif