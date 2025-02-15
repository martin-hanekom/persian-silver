#ifndef PERSIAN_SILVER_GAME_HPP
#define PERSIAN_SILVER_GAME_HPP

#include <SFML/Graphics.hpp>
#include "board.hpp"

class Game
{
public:
    Game(Game const&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game const&) = delete;
    Game& operator=(Game&&) = delete;

    static Game& get();

    void run();
    void onClosed();
    void onKeyPressed(sf::Event::KeyPressed const& keyPressed);
    void onMouseMoved(sf::Event::MouseMoved const& mouseMove);
    void onMouseButtonPressed(sf::Event::MouseButtonPressed const& mouseButton);
    void onMouseWheelScrolled(sf::Event::MouseWheelScrolled const& mouseScroll);

    static constexpr size_t tileDepth = 7u;

private:
    Game();
    ~Game();

    Board board;
    sf::Vector2f mouseClickPosition;
    bool mouseDragging = false;
};

#endif