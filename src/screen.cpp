#include "screen.hpp"

namespace silver
{

Screen::Screen()
{
    window.setVerticalSyncEnabled(true);
    mainView.zoom(defaultZoom);
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


void Screen::draw(sf::Drawable const& drawable)
{
    Screen::getWindow().draw(drawable);
}

sf::Vector2f Screen::mainViewCoords(sf::Vector2i pixels) const
{
    return window.mapPixelToCoords(pixels, mainView);
}

sf::Vector2f Screen::uiViewCoords(sf::Vector2i pixels) const
{
    return window.mapPixelToCoords(pixels, uiView);
}

void Screen::zoom(float factor)
{
    mainView.zoom(factor);
}

void Screen::pan(sf::Vector2f offset)
{
    mainView.move(offset);
}

void Screen::setMainView()
{
    window.setView(mainView);
}

void Screen::setUIView()
{
    window.setView(uiView);
}

}