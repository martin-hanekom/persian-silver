#ifndef PERSIAN_SILVER_UI_HPP
#define PERSIAN_SILVER_UI_HPP

#include <functional>
#include <SFML/Graphics.hpp>

namespace silver
{

class Interaction
{
public:
    virtual bool onMouseMoved(sf::Vector2f mousePos);
    virtual bool onLeftClick();
    virtual bool onRightClick();

protected:
    virtual bool touches(sf::Vector2f mousePos) = 0;
    virtual void onHover();
    virtual void offHover();

    bool hovering = false;
};

class Sprite
{
public:
    Sprite(sf::Vector2f pos);

    virtual void draw() const = 0;
    virtual void setPosition(sf::Vector2f newPos);
    virtual void setFillColor(sf::Color newColor);
    virtual void setHoverColor(sf::Color newColor);

    sf::Vector2f getPosition() const;

protected:
    sf::Vector2f pos;
    sf::Color color;
    sf::Color hoverColor;
};

class Circle : public Interaction, Sprite
{
public:
    Circle(sf::Vector2f pos, float radius, size_t pointCount = 30, bool centered = false);

    virtual void draw() const override;
    virtual void setPosition(sf::Vector2f newPos) override;
    virtual void setFillColor(sf::Color newColor) override;
    virtual void setHoverColor(sf::Color newColor) override;
    virtual void setRadius(float radius);

    float getRadius() const;

protected:
    bool touches(sf::Vector2f mousePos) override;
    void onHover() override;
    void offHover() override;

    sf::CircleShape shape;
};

class Rectangle : public Interaction, Sprite
{
public:
    Rectangle(sf::Vector2f pos, sf::Vector2f size, bool centered = false);

    virtual void draw() const override;
    virtual void setPosition(sf::Vector2f newPos) override;
    virtual void setFillColor(sf::Color newColor) override;
    virtual void setHoverColor(sf::Color newColor) override;
    virtual void setSize(sf::Vector2f size);

    sf::Vector2f getSize() const;

protected:
    bool touches(sf::Vector2f mousePos) override;
    void offHover() override;
    void onHover() override;

    sf::RectangleShape shape;
};

class Button : public Rectangle
{
public:
    Button(sf::Vector2f pos, sf::Vector2f size, std::function<void()> callback, std::string const& message = {});

    void setTextColor(sf::Color color);
    void setCharacterSize(unsigned size);

    void draw() const override;
    bool onLeftClick() override;

protected:
    std::function<void()> callback;
    sf::Text text;
};

}

#endif