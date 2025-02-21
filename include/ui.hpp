#ifndef PERSIAN_SILVER_UI_HPP
#define PERSIAN_SILVER_UI_HPP

#include <functional>
#include <SFML/Graphics.hpp>

class Button
{
public:
    Button(sf::Vector2f size, std::string const& text, std::function<void()> callback);
    void setPosition(sf::Vector2f position);
    void setFillColor(sf::Color color);
    void setTextColor(sf::Color color);
    void setCharacterSize(unsigned size);
    sf::Vector2f getSize() const;

    void draw() const;
    bool onMouseMoved(sf::Vector2f mousePosition);
    bool onLeftClick();
    bool onRightClick();

    static constexpr sf::Color hoverColor{sf::Color::Magenta};

private:
    sf::RectangleShape shape;
    sf::Text text;
    std::function<void()> callback;
    bool hovering = false;
    sf::Color color;
};

#endif