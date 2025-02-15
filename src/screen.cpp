#include "screen.hpp"

sf::RenderWindow& Screen::getWindow()
{
    static sf::RenderWindow window(sf::VideoMode({1920u, 1080u}), "Persian Silver", sf::State::Fullscreen);
    return window;
}

sf::Font& Screen::getFont()
{
    static sf::Font font("assets/arial.ttf");
    return font;
}

void Screen::init()
{
    auto& window = Screen::getWindow();
    window.setVerticalSyncEnabled(true);
    sf::View view({0.f, 0.f}, {1920.f, 1080.f});
    window.setView(view);
}

void Screen::draw(sf::Drawable const& drawable)
{
    Screen::getWindow().draw(drawable);
}