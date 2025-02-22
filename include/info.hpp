#ifndef PERSIAN_SILVER_INFO_HPP
#define PERSIAN_SILVER_INFO_HPP

#include <cmath>
#include <SFML/Graphics.hpp>
#include "asset.hpp"
#include "player.hpp"

class Info
{
public:
    Info();
    void draw() const;
    void setPlayer(Player const& player);

    static constexpr float panelSize = 200.f;
    static constexpr sf::Color panelColor{76, 88, 91};
    static constexpr sf::Color panelOutline{sf::Color::Black};

    static constexpr float iconRadius = 15.f;
    static constexpr float iconPadding = 5.f;
    static constexpr size_t iconSides = 6;
    static constexpr sf::Color iconOutline{sf::Color::White};
    static constexpr float iconRotation = M_PI / iconSides;

private:
    sf::RectangleShape panel{{panelSize, panelSize}};
    sf::CircleShape icon{iconRadius, iconSides};
    sf::Text playerName{Asset::getFont(), ""};
};

#endif
