#ifndef PERSIAN_SILVER_INFO_HPP
#define PERSIAN_SILVER_INFO_HPP

#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "asset.hpp"
#include "screen.hpp"
#include "player.hpp"
#include "ui.hpp"
#include "tile.hpp"
#include "resource.hpp"

namespace silver
{

class PlayerInfo : public Rectangle
{
public:
    PlayerInfo(sf::Vector2f pos, float width);

    void draw() const;
    void setPlayer(Player const& player);

    static constexpr float iconRadius = 15.f;
    static constexpr float iconDiameter = 2.f * iconRadius;
    static constexpr size_t iconSides = 6;
    static constexpr sf::Color iconOutline{sf::Color::White};
    static constexpr float iconRotation = M_PI / iconSides;
    static constexpr float glyphRadius = 25.f;
    static constexpr float glyphDiameter = 2.f * glyphRadius;
    static constexpr sf::Vector2f padding{10.f, 10.f};
    static constexpr float height = iconDiameter + 2.f * padding.y + 2.f * (glyphDiameter + padding.y);

private:
    sf::CircleShape icon{iconRadius, iconSides};
    sf::Text playerName{Asset::getFont(), ""};
    Glyph goldTile;
    Glyph foodTile;
    sf::Text gold{Asset::getFont(), ""};
    sf::Text goldTax{Asset::getFont(), ""};
    sf::Text food{Asset::getFont(), ""};
    sf::Text foodTax{Asset::getFont(), ""};
};

class PieceInfo : public Rectangle
{
public:
    PieceInfo(sf::Vector2f pos, float width);

    void draw() const;
    void setPiece(Piece* const piece);

    bool onMouseMoved(sf::Vector2f mousePos) override;
    bool onLeftClick() override;
    bool onRightClick() override;
    //void setPosition(sf::Vector2f newPos) override;

    static constexpr size_t menuSize = 6;
    static constexpr size_t pieceNameSize = 30u;
    static constexpr sf::Vector2f padding{10.f, 10.f};
    static constexpr float height = pieceNameSize + 2.f * padding.y + menuSize * (MenuTile::tileSize + padding.y);

    MenuTile* hovering = nullptr;
    MenuTile* selected = nullptr;

private:
    void clearMenu();

    sf::Text pieceName{Asset::getFont(), ""};
    std::array<MenuTile, menuSize> buildMenu;
};

class Info : public Interaction
{
public:
    Info();
    void draw() const;
    void setPlayer(Player const& player);
    void setPiece(Piece* const piece);

    bool touches(sf::Vector2f mousePos) const;
    bool onMouseMoved(sf::Vector2f mousePos);
    bool onLeftClick();
    bool onRightClick();

    static constexpr sf::Vector2f panelSize{220.f, Screen::windowSize.y};
    static constexpr sf::Vector2f padding{10.f, 10.f};
    static constexpr sf::Color panelColor{76, 88, 91};
    static constexpr sf::Color panelOutline{sf::Color::Black};

    static constexpr sf::Vector2f nextSize{panelSize.x - 2.f * padding.x, 45.f};

private:
    Rectangle panel;
    PlayerInfo playerInfo;
    PieceInfo pieceInfo;
    Button next;
};

}

#endif
