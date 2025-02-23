#ifndef PERSIAN_SILVER_INFO_HPP
#define PERSIAN_SILVER_INFO_HPP

#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "asset.hpp"
#include "screen.hpp"
#include "player.hpp"
#include "ui.hpp"

class Info
{
public:
    Info();
    void draw() const;
    void setPlayer(Player const& player);
    void setPiece(Piece* const piece);

    bool onMouseMoved(sf::Vector2f mousePosition);
    bool onLeftClick();
    bool onRightClick();

    static constexpr sf::Vector2f panelSize{200.f, Screen::windowSize.y};
    static constexpr sf::Vector2f padding{10.f, 10.f};
    static constexpr sf::Color panelColor{76, 88, 91};
    static constexpr sf::Color panelOutline{sf::Color::Black};

    static constexpr float iconRadius = 15.f;
    static constexpr size_t iconSides = 6;
    static constexpr sf::Color iconOutline{sf::Color::White};
    static constexpr float iconRotation = M_PI / iconSides;
    static constexpr size_t menuSize = 6;

    static constexpr sf::Vector2f nextSize{panelSize.x - 2.f * padding.x, 30.f};

private:
    void clearMenu();

    sf::RectangleShape panel{panelSize};
    sf::CircleShape icon{iconRadius, iconSides};
    sf::Text playerName{Asset::getFont(), ""};
    sf::Text pieceName{Asset::getFont(), ""};
    Button next;
    std::array<MenuTile, menuSize> buildMenu;
};

#endif
