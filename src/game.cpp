#include "game.hpp"
#include "screen.hpp"

Game::Game(): board(tileDepth)
{
}

Game::~Game()
{
}

Game& Game::get()
{
    static Game game;
    return game;
}

void Game::run()
{
    auto& window = Screen::getWindow();

    while (window.isOpen())
    {
        window.handleEvents(
            [this](sf::Event::Closed const&) { onClosed(); },
            [this](sf::Event::KeyPressed const& keyPressed) { onKeyPressed(keyPressed); },
            [this](sf::Event::MouseButtonPressed const& mouseButton) { onMouseButtonPressed(mouseButton); },
            [this](sf::Event::MouseMoved const& mouseMove) { onMouseMoved(mouseMove); },
            [this](sf::Event::MouseWheelScrolled const& mouseScroll) { onMouseWheelScrolled(mouseScroll); }
        );

        window.clear();
        board.draw();
        window.display();
    }
}

void Game::onClosed()
{
    Screen::getWindow().close();
}

void Game::onKeyPressed(sf::Event::KeyPressed const& keyPressed)
{
    switch (keyPressed.scancode)
    {
        case sf::Keyboard::Scancode::Escape:
            onClosed();
            break;
        default:
            break;
    }
}

void Game::onMouseMoved(sf::Event::MouseMoved const& mouseMove)
{
    auto& screen = Screen::get();
    auto mousePosition = screen.mapPixelToCoords(mouseMove.position);

    if (mouseDragging && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        screen.pan(mouseClickPosition - mousePosition);
    }
    else
    {
        mouseDragging = false;
        board.onMouseMoved(mousePosition);
    }
}

void Game::onMouseButtonPressed(sf::Event::MouseButtonPressed const& mouseButton)
{
    auto& screen = Screen::get();
    mouseClickPosition = screen.mapPixelToCoords(mouseButton.position);
    mouseDragging = true;

    switch (mouseButton.button)
    {
        case sf::Mouse::Button::Left:
            board.onLeftClick();
            break;
        case sf::Mouse::Button::Right:
            board.onRightClick();
            break;
        default:
            break;
    }
}

void Game::onMouseWheelScrolled(sf::Event::MouseWheelScrolled const& mouseScroll)
{
    auto& window = Screen::getWindow();
    if (mouseScroll.wheel == sf::Mouse::Wheel::Vertical)
    {
        Screen::get().zoom(1.f - mouseScroll.delta * 0.1f);
    }
}