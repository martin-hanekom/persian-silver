#include <algorithm>
#include "tile.hpp"
#include "action.hpp"
#include "game.hpp"

namespace silver
{

void Tile::setPiece(Piece* newPiece)
{
    piece = newPiece;
    if (nullptr != piece && !piece->isTile(this))
    {
        piece->setTile(this);
    }
}

Piece* Tile::getPiece()
{
    return piece;
}

bool Tile::hasPiece() const
{
    return piece != nullptr;
}

bool Tile::isPiece(Piece* newPiece) const
{
    return piece == newPiece;
}

BoardTile::BoardTile(sf::Vector2f pos, int depth)
    : Circle(pos, tileRadius, tileSides, true), depth(depth)
{
    setFillColor(std::rand() % 2 ? lightGrass : darkGrass);
    setHoverColor(defaultHoverColor);
    shape.setRotation(sf::radians(tileRotation));
}

void BoardTile::setNewNeighbor(size_t index, BoardTile* other)
{
    assert(nullptr != other);
    neighbors[index] = other;
    other->setNeighbor(opposite(index), this);

    auto leftIndex = (index + tileSides - 1) % tileSides;
    auto rightIndex = (index + 1) % tileSides;
    if (auto left = getNeighbor(leftIndex); left != nullptr)
    {
        auto leftNeighborIndex = (opposite(leftIndex) + tileSides - 1) % tileSides;
        left->setNeighbor(leftNeighborIndex, other);
        other->setNeighbor(opposite(leftNeighborIndex), left);
    }

    if (auto right = getNeighbor(rightIndex); right != nullptr)
    {
        auto rightNeighborIndex = (opposite(rightIndex) + 1) % tileSides;
        right->setNeighbor(rightNeighborIndex, other);
        other->setNeighbor(opposite(rightNeighborIndex), right);
    }
}

void BoardTile::setNeighbor(size_t index, BoardTile* other)
{
    neighbors[index] = other;
}

BoardTile* BoardTile::getNeighbor(size_t index)
{
    return hasNeighbor(index) ? neighbors[index] : nullptr;
}

bool BoardTile::hasNeighbor(size_t index) const
{
    return neighbors[index] != nullptr;
}

bool BoardTile::isNeighbor(BoardTile const* other) const
{
    return std::find(neighbors.cbegin(), neighbors.cend(), other) != neighbors.cend();
}

sf::Vector2f BoardTile::getNeigborPosition(size_t index) const
{
    auto position = shape.getPosition();
    position.x += 2 * (tileRadius + tilePadding) * std::sin(2 * M_PI * index / tileSides);
    position.y += -2 * (tileRadius + tilePadding) * std::cos(2 * M_PI * index / tileSides);
    return position;
}

sf::Vector2f BoardTile::getPosition() const
{
    return Circle::getPosition();
}

float BoardTile::getPieceWidth() const
{
    return pieceFillRatio * 2.f * getRadius();
}

void BoardTile::draw() const
{
    Circle::draw();
    if (hasPiece())
    {
        piece->draw();
    }
}

bool BoardTile::onLeftClick()
{
    if (selected)
    {
        offSelect();
    }
    else if (hovering)
    {
        onSelect();
    }

    return hovering;
}

constexpr size_t BoardTile::opposite(size_t index)
{
    return (index + tileSides / 2) % tileSides;
}

void BoardTile::onHover()
{
    if (!selected)
    {
        shape.setFillColor(hoverColor);
    }
}

void BoardTile::offHover()
{
    if (!selected)
    {
        shape.setFillColor(color);
    }
}
void BoardTile::onSelect()
{
    selected = true;
    shape.setFillColor(selectColor);
}

void BoardTile::offSelect()
{
    selected = false;
    shape.setFillColor(color);
}

MenuTile::MenuTile(sf::Vector2f pos) :
    Rectangle(pos, {tileSize, tileSize}, true),
    goldTile({0.f, 0.f}, glyphRadius),
    foodTile({0.f, 0.f}, glyphRadius)
{
    setPosition(pos);
    setFillColor(tileColor);
    setHoverColor(defaultHoverColor);

    goldTile.setResource(Resource::create(ResourceType::Gold));
    foodTile.setResource(Resource::create(ResourceType::Food));
}

sf::Vector2f MenuTile::getPosition() const
{
    return Rectangle::getPosition();
}

float MenuTile::getPieceWidth() const
{
    return pieceFillRatio * getSize().x;
}

void MenuTile::draw() const
{
    Rectangle::draw();
    if (hasPiece())
    {
        piece->draw();
        goldTile.draw();
        foodTile.draw();
    }
}

bool MenuTile::onLeftClick()
{
    if (hovering)
    {
        Game::submit(BuildAction(this));
    }
    return hovering;
}

void MenuTile::setPosition(sf::Vector2f pos)
{
    Rectangle::setPosition(pos);
    goldTile.setPosition(pos + sf::Vector2f{tileHalfSize + glyphRadius + padding.x, -glyphRadius - padding.y});
    foodTile.setPosition(pos + sf::Vector2f{tileHalfSize + glyphRadius + padding.x, glyphRadius + padding.y});
}

Glyph::Glyph(sf::Vector2f pos, float radius) : Circle(pos, radius, tileSides, true)
{
    setFillColor(tileColor);
}

Glyph::~Glyph()
{
    if (nullptr != resource)
    {
        delete resource;
    }
}

void Glyph::setPosition(sf::Vector2f pos)
{
    Circle::setPosition(pos);
    if (hasResource())
    {
        resource->setPosition(pos);
    }
}

sf::Vector2f Glyph::getPosition() const
{
    return Circle::getPosition();
}

float Glyph::getResourceWidth() const
{
    return resourceFillRatio * 2.f * getRadius();
}

void Glyph::draw() const
{
    Circle::draw();
    if (hasResource())
    {
        resource->draw();
    }
}

void Glyph::setResource(Resource* newResource)
{
    resource = newResource;
    if (nullptr != resource && !resource->isGlyph(this))
    {
        resource->setGlyph(this);
    }
}

bool Glyph::isResource(Resource* newResource) const
{
    return resource == newResource;
}

bool Glyph::hasResource() const
{
    return resource != nullptr;
}

}