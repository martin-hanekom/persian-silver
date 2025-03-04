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

bool BoardTile::isNeighbor(BoardTile const* other, size_t range) const
{
    if (std::count(neighbors.cbegin(), neighbors.cend(), other))
    {
        return true;
    }

    if (range < 2)
    {
        return false;
    }

    for (auto const neighbor : neighbors)
    {
        if (neighbor->isNeighbor(other, range-1))
        {
            return true;
        }
    }

    return false;
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
    gold.setFillColor(sf::Color::Black);
    gold.setCharacterSize(textSize);
    food.setFillColor(sf::Color::Black);
    food.setCharacterSize(textSize);
}

sf::Vector2f MenuTile::getPosition() const
{
    return Rectangle::getPosition();
}

float MenuTile::getPieceWidth() const
{
    return pieceFillRatio * getSize().x;
}

void MenuTile::setPiece(Piece* piece)
{
    offSelect();
    Tile::setPiece(piece);
    if (nullptr != piece)
    {
        auto const& cost = piece->getCost();
        gold.setString(cost.goldText());
        food.setString(cost.foodText());
    }
}

void MenuTile::draw() const
{
    Rectangle::draw();
    if (hasPiece())
    {
        piece->draw();
        goldTile.draw();
        foodTile.draw();
        Screen::draw(gold);
        Screen::draw(food);
        //Screen::draw(goldTax);
        //Screen::draw(foodTax);
    }
}

bool MenuTile::onLeftClick()
{
    if (selected)
    {
        offSelect();
    }
    else if (hovering)
    {
        onSelect();
        Game::submit(MenuSelectAction(this));
    }

    return hovering;
}

void MenuTile::onHover()
{
    if (!selected)
    {
        shape.setFillColor(hoverColor);
    }
}

void MenuTile::offHover()
{
    if (!selected)
    {
        shape.setFillColor(color);
    }
}

void MenuTile::onSelect()
{
    selected = true;
    shape.setFillColor(selectColor);
}

void MenuTile::offSelect()
{
    selected = false;
    shape.setFillColor(color);
}

void MenuTile::setPosition(sf::Vector2f pos)
{
    Rectangle::setPosition(pos);
    goldTile.setPosition(pos + sf::Vector2f{tileHalfSize + glyphRadius + padding.x, -glyphRadius - padding.y});
    foodTile.setPosition(pos + sf::Vector2f{tileHalfSize + glyphRadius + padding.x, glyphRadius + padding.y});
    gold.setPosition(goldTile.getPosition() + sf::Vector2f{glyphRadius + padding.x, -glyphRadius});
    food.setPosition(foodTile.getPosition() + sf::Vector2f{glyphRadius + padding.x, -glyphRadius});
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