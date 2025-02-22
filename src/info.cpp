#include "info.hpp"
#include "screen.hpp"

Info::Info()
{
    panel.setPosition(Screen::getCornerOffset<Screen::Corner::TopLeft>());
    panel.setFillColor(panelColor);
    panel.setOutlineColor(panelOutline);
    panel.setOutlineThickness(2.f);

    icon.setRotation(sf::radians(iconRotation));
    icon.setPosition(panel.getPosition() + sf::Vector2f{iconRadius + iconPadding, iconRadius + iconPadding});
    icon.setOutlineColor(iconOutline);
    icon.setOutlineThickness(1.f);

    playerName.setPosition(icon.getPosition() + sf::Vector2f{iconRadius * 2.f, 0.f});
    playerName.setFillColor(sf::Color::Black);
}

void Info::draw() const
{
    Screen::draw(panel);
    Screen::draw(icon);
    Screen::draw(playerName);
}

void Info::setPlayer(Player const& player)
{
    icon.setFillColor(player.getColor());
    playerName.setString(player.getName());
}