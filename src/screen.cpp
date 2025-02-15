#include "screen.hpp"

Screen::Screen()
{
    window.setVerticalSyncEnabled(true);
    sf::View view({0.f, 0.f}, {1920.f, 1080.f});
    //view.zoom(2.0f);
    window.setView(view);
}

Screen::~Screen()
{
    window.close();
}

Screen& Screen::get()
{
    static Screen screen;
    return screen;
}

sf::RenderWindow& Screen::getWindow()
{
    return get().window;
}

sf::Font& Screen::getFont()
{
    static sf::Font font("assets/arial.ttf");
    return font;
}

void Screen::draw(sf::Drawable const& drawable)
{
    Screen::getWindow().draw(drawable);
}

sf::Vector2f Screen::mapPixelToCoords(sf::Vector2i pixels) const
{
    return window.mapPixelToCoords(pixels);
}

void Screen::zoom(float factor)
{
    auto view = window.getView();
    view.zoom(factor);
    window.setView(view);
}

void Screen::pan(sf::Vector2f offset)
{
    auto view = window.getView();
    view.move(offset);
    window.setView(view);
}