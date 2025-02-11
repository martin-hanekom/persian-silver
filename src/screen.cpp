#include "screen.hpp"

sf::RenderWindow& Screen::getWindow()
{
    static sf::RenderWindow window(sf::VideoMode({1920u, 1080u}), "Persian Silver", sf::State::Fullscreen);
    return window;
}

void Screen::init()
{
    auto& window = Screen::getWindow();
    window.setVerticalSyncEnabled(true);
    sf::View view({0.f, 0.f}, {1920.f, 1080.f});
    window.setView(view);
}

bool Screen::isOpen()
{
    auto const& window = Screen::getWindow();
    return window.isOpen();
}

void Screen::clear()
{
    auto& window = Screen::getWindow();
    window.clear();
}

void Screen::handleEvents()
{
    auto& window = Screen::getWindow();
    window.handleEvents(
        [](sf::Event::Closed const&) { onClosed(); },
        [](sf::Event::KeyPressed const& keyPressed) { onKeyPressed(keyPressed); },
        [](sf::Event::MouseWheelScrolled const& mouseScroll) { onMouseWheelScrolled(mouseScroll); });
}

void Screen::display()
{
    auto& window = Screen::getWindow();
    window.display();
}

void Screen::draw(sf::Drawable const& drawable)
{
    auto& window = Screen::getWindow();
    window.draw(drawable);
}

void Screen::onClosed()
{
    auto& window = Screen::getWindow();
    window.close();
}

void Screen::onKeyPressed(sf::Event::KeyPressed const& keyPressed)
{
    auto& window = Screen::getWindow();
    if (keyPressed.scancode == sf::Keyboard::Scancode::Escape)
    {
        window.close();
    }
}

void Screen::onMouseWheelScrolled(sf::Event::MouseWheelScrolled const& mouseScroll)
{
    auto& window = Screen::getWindow();
    if (mouseScroll.wheel == sf::Mouse::Wheel::Vertical)
    {
        auto const zoomFactor = 1.1f;
        auto view = window.getView();
        if (mouseScroll.delta > 0)
        {
            view.zoom(1.f / zoomFactor);
        }
        else if (mouseScroll.delta < 0)
        {
            view.zoom(zoomFactor);
        }
        window.setView(view);
    }
}