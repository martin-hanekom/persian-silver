#include "ui.hpp"
#include "asset.hpp"
#include "screen.hpp"
#include "util.hpp"

namespace silver
{

bool Interaction::onMouseMoved(sf::Vector2f mousePos)
{
    auto newHovering = touches(mousePos);
    if (!hovering && newHovering)
    {
        onHover();
    }
    else if (hovering && !newHovering)
    {
        offHover();
    }
    hovering = newHovering;
    return hovering;
}

bool Interaction::onLeftClick()
{
    return hovering;
}

bool Interaction::onRightClick()
{
    return hovering;
}

void Interaction::onHover()
{
}

void Interaction::offHover()
{
}

Hoverable::Hoverable(sf::Vector2f pos) : pos(pos)
{
}

void Hoverable::setPosition(sf::Vector2f newPos)
{
    pos = newPos;
}

void Hoverable::setFillColor(sf::Color newColor)
{
    color = newColor;
}

void Hoverable::setHoverColor(sf::Color newColor)
{
    hoverColor = newColor;
}

sf::Vector2f Hoverable::getPosition() const
{
    return pos;
}

Circle::Circle(sf::Vector2f pos, float radius, size_t pointCount, bool centered) : Hoverable(pos), shape(radius, pointCount)
{
    shape.setPosition(pos);
    if (centered)
    {
        shape.setOrigin({radius, radius});
    }
}

void Circle::draw() const
{
    Screen::draw(shape);
}

void Circle::setPosition(sf::Vector2f newPos)
{
    Hoverable::setPosition(newPos);
    shape.setPosition(newPos);
}

void Circle::setFillColor(sf::Color newColor)
{
    Hoverable::setFillColor(newColor);
    if (!hovering)
    {
        shape.setFillColor(newColor);
    }
}

void Circle::setHoverColor(sf::Color newColor)
{
    Hoverable::setHoverColor(newColor);
    if (hovering)
    {
        shape.setFillColor(newColor);
    }
}

sf::CircleShape& Circle::getShape()
{
    return shape;
}

bool Circle::touches(sf::Vector2f mousePos) const
{
    return distance(pos, mousePos) < shape.getRadius();
}

void Circle::onHover()
{
    shape.setFillColor(hoverColor);
}

void Circle::offHover()
{
    shape.setFillColor(color);
}

void Circle::setRadius(float radius)
{
    shape.setRadius(radius);
}

float Circle::getRadius() const
{
    return shape.getRadius();
}

Rectangle::Rectangle(sf::Vector2f pos, sf::Vector2f size, bool centered) : Hoverable(pos), shape(size)
{
    shape.setPosition(pos);
    if (centered)
    {
        shape.setOrigin(shape.getLocalBounds().getCenter());
    }
}

void Rectangle::draw() const
{
    Screen::draw(shape);
}

void Rectangle::setPosition(sf::Vector2f newPos)
{
    Hoverable::setPosition(newPos);
    shape.setPosition(newPos);
}

void Rectangle::setFillColor(sf::Color newColor)
{
    Hoverable::setFillColor(newColor);
    if (!hovering)
    {
        shape.setFillColor(newColor);
    }
}

void Rectangle::setHoverColor(sf::Color newColor)
{
    Hoverable::setHoverColor(newColor);
    if (hovering)
    {
        shape.setFillColor(newColor);
    }
}

sf::RectangleShape& Rectangle::getShape()
{
    return shape;
}

bool Rectangle::touches(sf::Vector2f mousePos) const
{
    return shape.getGlobalBounds().contains(mousePos);
}

void Rectangle::onHover()
{
    shape.setFillColor(hoverColor);
}

void Rectangle::offHover()
{
    shape.setFillColor(color);
}

void Rectangle::setSize(sf::Vector2f size)
{
    shape.setSize(size);
}

sf::Vector2f Rectangle::getSize() const
{
    return shape.getSize();
}

Button::Button(sf::Vector2f pos, sf::Vector2f size, std::function<void()> callback, std::string const& message)
    : Rectangle(pos, size), callback(callback), text(Asset::getFont(), message)
{
    text.setPosition(shape.getGlobalBounds().getCenter());
    text.setOrigin(text.getLocalBounds().getCenter());
}

void Button::setPosition(sf::Vector2f newPos)
{
    Rectangle::setPosition(newPos);
    text.setPosition(shape.getGlobalBounds().getCenter());
}

void Button::setTextColor(sf::Color color)
{
    text.setFillColor(color);
}

void Button::setCharacterSize(unsigned size)
{
    text.setCharacterSize(size);
}

void Button::draw() const
{
    Rectangle::draw();
    if (!text.getString().isEmpty())
    {
        Screen::draw(text);
    }
}

bool Button::onLeftClick()
{
    if (hovering)
    {
        callback();
    }
    return hovering;
}

}