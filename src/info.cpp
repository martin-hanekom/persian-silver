#include <iostream>
#include "info.hpp"
#include "screen.hpp"
#include "game.hpp"

Info::Info(): next(Game::nextPlayerCallback, nextSize, "next")
{
    panel.setPosition(Screen::getCornerOffset<Screen::Corner::TopLeft>());
    panel.setFillColor(panelColor);
    panel.setOutlineColor(panelOutline);
    panel.setOutlineThickness(2.f);

    icon.setPosition(panel.getPosition() + padding);
    icon.setOutlineColor(iconOutline);
    icon.setOutlineThickness(1.f);

    playerName.setPosition(icon.getPosition() + sf::Vector2f{iconRadius * 3.f, 0.f});
    playerName.setFillColor(sf::Color::Black);

    pieceName.setPosition(icon.getPosition() + sf::Vector2f{0.f, iconRadius * 3.f});
    pieceName.setFillColor(sf::Color::Black);

    next.setFillColor(sf::Color::Red);
    next.setTextColor(sf::Color::Black);
    next.setPosition(Screen::getCornerOffset<Screen::Corner::BottomLeft>() + sf::Vector2f{padding.x, -padding.y - next.getSize().y});

    auto menuStart = pieceName.getPosition() + sf::Vector2f{0.f, pieceName.getLocalBounds().size.y + padding.y};
    for (auto i = 0u; i < menuSize; ++i)
    {
        buildMenu[i].setPosition(menuStart + sf::Vector2f{0.f, i * (MenuTile::tileSize + padding.y)});
    }
}

void Info::draw() const
{
    Screen::draw(panel);
    Screen::draw(icon);
    Screen::draw(playerName);
    Screen::draw(pieceName);
    next.draw();
    for (auto const& menuTile : buildMenu)
    {
        menuTile.draw();
    }
}

bool Info::onMouseMoved(sf::Vector2f mousePosition)
{
    return next.onMouseMoved(mousePosition);
}

bool Info::onLeftClick()
{
    return next.onLeftClick();
}

bool Info::onRightClick()
{
    return next.onRightClick();
}

void Info::setPlayer(Player const& player)
{
    icon.setFillColor(player.getColor());
    playerName.setString(player.getName());
}

void Info::setPiece(Piece* const piece)
{
    clearMenu();

    if (nullptr == piece)
    {
        pieceName.setString({});
    }
    else
    {
        pieceName.setString(piece->getName());
        auto index = 0u;
        for (auto const& pieceType : piece->buildable())
        {
            buildMenu[index++].setPiece(Piece::create(pieceType, piece->getPlayer(), nullptr));
        }
    }
}

void Info::clearMenu()
{
    for (auto& menuTile : buildMenu)
    {
        menuTile.setPiece(nullptr);
    }
}