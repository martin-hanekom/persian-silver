#ifndef PERSIAN_SILVER_SCREEN_HPP
#define PERSIAN_SILVER_SCREEN_HPP

#include <SFML/Graphics.hpp>

class Screen
{
public:
    static sf::RenderWindow& getWindow();
    static sf::Font& getFont();
    static void init();
    static void draw(sf::Drawable const& drawable);

private:
    static constexpr sf::Vector2f windowSize = {1920.f, 1080.f};
};

#endif