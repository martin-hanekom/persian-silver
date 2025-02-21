#include "ui.hpp"
#include "asset.hpp"
#include "screen.hpp"

Button::Button(sf::Vector2f size, std::string const& message, std::function<void()> callback)
    : shape(size), text(Asset::getFont(), message), callback(callback)
{
    shape.setOrigin(shape.getLocalBounds().getCenter());
    text.setOrigin(text.getLocalBounds().getCenter());
}

void Button::setPosition(sf::Vector2f position)
{
    shape.setPosition(position);
    text.setPosition(position);
}

void Button::setFillColor(sf::Color newColor)
{
    color = newColor;
    shape.setFillColor(color);
}

void Button::setTextColor(sf::Color color)
{
    text.setFillColor(color);
}

void Button::setCharacterSize(unsigned size)
{
    text.setCharacterSize(size);
}

sf::Vector2f Button::getSize() const
{
    return shape.getSize();
}

void Button::draw() const
{
    Screen::draw(shape);
    Screen::draw(text);
}

bool Button::onMouseMoved(sf::Vector2f mousePosition)
{
    if (shape.getGlobalBounds().contains(mousePosition))
    {
        if (!hovering)
        {
            shape.setFillColor(hoverColor);
        }
        hovering = true;
    }
    else
    {
        if (hovering)
        {
            shape.setFillColor(color);
        }
        hovering = false;
    }

    return hovering;
}

bool Button::onLeftClick()
{
    if (!hovering)
    {
        return false;
    }

    callback();
    return true;
}

bool Button::onRightClick()
{
    return false;
}