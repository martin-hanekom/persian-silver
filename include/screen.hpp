#ifndef PERSIAN_SILVER_SCREEN_HPP
#define PERSIAN_SILVER_SCREEN_HPP

#include <SFML/Graphics.hpp>

class Screen
{
public:
    static sf::RenderWindow& getWindow();
    static void init();
    static bool isOpen();
    static void clear();
    static void handleEvents();
    static void draw(sf::Drawable const& drawable);
    static void display();
    static void onClosed();
    static void onKeyPressed(sf::Event::KeyPressed const& keyPressed);
    static void onMouseWheelScrolled(sf::Event::MouseWheelScrolled const& mouseScroll);

private:
    static constexpr sf::Vector2f windowSize = {1920.f, 1080.f};
};

#endif