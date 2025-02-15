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
    Screen::init();
    auto& window = Screen::getWindow();

    while (window.isOpen())
    {
        window.handleEvents(
            [this](sf::Event::Closed const&) { onClosed(); },
            [this](sf::Event::KeyPressed const& keyPressed) { onKeyPressed(keyPressed); },
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
    auto& window = Screen::getWindow();
    auto mousePosition = window.mapPixelToCoords(mouseMove.position);
    board.onMouseMoved(mousePosition);
}

void Game::onMouseWheelScrolled(sf::Event::MouseWheelScrolled const& mouseScroll)
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
    /*
    auto mousePosition = window.mapPixelToCoords({mouseScroll.x, mouseScroll.y});
    for (auto& tile : board.tiles)
    {
        if (tile.shape.getGlobalBounds().contains(mousePosition))
        {
            tile.onHover();
        }
    }
        */
}