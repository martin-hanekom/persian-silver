#include <iostream>
#include "info.hpp"
#include "screen.hpp"
#include "game.hpp"
#include "asset.hpp"

namespace silver
{

PlayerInfo::PlayerInfo(sf::Vector2f pos, float width) :
    Rectangle(pos, {width, height}, false),
    goldTile(pos + padding + sf::Vector2f{glyphRadius, iconDiameter + glyphRadius + padding.y}, glyphRadius),
    foodTile(goldTile.getPosition() + sf::Vector2f{0.f, glyphDiameter + padding.y}, glyphRadius)
{
    icon.setPosition(pos + padding);
    icon.setOutlineColor(iconOutline);
    icon.setOutlineThickness(1.f);

    playerName.setPosition(icon.getPosition() + sf::Vector2f{iconDiameter + padding.x, 0.f});
    playerName.setFillColor(sf::Color::Black);

    goldTile.setResource(Resource::create(ResourceType::Gold));
    foodTile.setResource(Resource::create(ResourceType::Food));

    goldText.setPosition(goldTile.getPosition() + sf::Vector2f{glyphRadius + padding.x, -glyphRadius});
    goldText.setFillColor(sf::Color::Black);
    foodText.setPosition(foodTile.getPosition() + sf::Vector2f{glyphRadius + padding.x, -glyphRadius});
    foodText.setFillColor(sf::Color::Black);
}

void PlayerInfo::setPlayer(Player const& player)
{
    icon.setFillColor(player.getColor());
    playerName.setString(player.getName());

    goldText.setString(std::to_string(player.getGold()));
    foodText.setString(std::to_string(player.getFood()));
}

void PlayerInfo::draw() const
{
    Screen::draw(icon);
    Screen::draw(playerName);
    goldTile.draw();
    foodTile.draw();
    Screen::draw(goldText);
    Screen::draw(foodText);
}

PieceInfo::PieceInfo(sf::Vector2f pos, float width) :
    Rectangle(pos, {width, height}, false)
{
    pieceName.setPosition(pos + padding);
    pieceName.setFillColor(sf::Color::Black);

    auto const half = MenuTile::tileSize / 2.f;
    auto const menuStart = pieceName.getPosition() + sf::Vector2f{half, pieceName.getLocalBounds().size.y + 2.f * padding.y + half + pieceName.getCharacterSize()};
    for (auto i = 0u; i < menuSize; ++i)
    {
        buildMenu[i].setPosition(menuStart + sf::Vector2f{0.f, i * (MenuTile::tileSize + padding.y)});
    }
}

void PieceInfo::draw() const
{
    Screen::draw(pieceName);
    for (auto const& menuTile : buildMenu)
    {
        menuTile.draw();
    }
}

bool PieceInfo::onMouseMoved(sf::Vector2f mousePos)
{
    if (nullptr != hovering && hovering->onMouseMoved(mousePos))
    {
        return true;
    }
    hovering = nullptr;

    for (auto& tile : buildMenu)
    {
        if (tile.onMouseMoved(mousePos))
        {
            hovering = &tile;
            return true;
        }
    }

    return false;
}

bool PieceInfo::onLeftClick()
{
    return false;
}

bool PieceInfo::onRightClick()
{
    return false;
}

void PieceInfo::setPiece(Piece* const piece)
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
            buildMenu[index++].setPiece(piece->getPlayer()->getMenuPiece(pieceType));
        }
    }
}

void PieceInfo::clearMenu()
{
    for (auto& menuTile : buildMenu)
    {
        menuTile.setPiece(nullptr);
    }
}

Info::Info() :
    panel(Screen::getCornerOffset<Screen::Corner::TopLeft>(), panelSize),
    playerInfo(panel.getPosition(), panelSize.x),
    pieceInfo(panel.getPosition() + sf::Vector2f{0.f, playerInfo.getSize().y}, panelSize.x),
    next({0.f, 0.f}, nextSize, Game::nextPlayerCallback, "next")
{
    panel.setFillColor(panelColor);
    panel.getShape().setOutlineColor(panelOutline);
    panel.getShape().setOutlineThickness(2.f);

    next.setFillColor(sf::Color::Red);
    next.setHoverColor(sf::Color::Magenta);
    next.setTextColor(sf::Color::Black);
    next.setPosition(Screen::getCornerOffset<Screen::Corner::BottomLeft>() + sf::Vector2f{padding.x, -padding.y - next.getSize().y});

}

void Info::draw() const
{
    panel.draw();
    playerInfo.draw();
    pieceInfo.draw();
    next.draw();

}

bool Info::touches(sf::Vector2f mousePos) const
{
    return panel.touches(mousePos);
}

bool Info::onMouseMoved(sf::Vector2f mousePos)
{
    return pieceInfo.onMouseMoved(mousePos) || next.onMouseMoved(mousePos);
}

bool Info::onLeftClick()
{
    return pieceInfo.onLeftClick() || next.onLeftClick();
}

bool Info::onRightClick()
{
    return pieceInfo.onRightClick() || next.onRightClick();
}

void Info::setPlayer(Player const& player)
{
    playerInfo.setPlayer(player);
}

void Info::setPiece(Piece* const piece)
{
    pieceInfo.setPiece(piece);
}

}