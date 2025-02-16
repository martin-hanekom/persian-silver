#ifndef PERSIAN_SILVER_GAME_HPP
#define PERSIAN_SILVER_GAME_HPP

#include <SFML/Graphics.hpp>
#include "board.hpp"
#include "player.hpp"

class Game
{
public:
    Game(Game const&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game const&) = delete;
    Game& operator=(Game&&) = delete;

    static Game& get();

    void run(size_t playerCount);
    void draw() const;
    void onClosed();
    void onKeyPressed(sf::Event::KeyPressed const& keyPressed);
    void onMouseMoved(sf::Event::MouseMoved const& mouseMove);
    void onMouseButtonPressed(sf::Event::MouseButtonPressed const& mouseButton);
    void onMouseWheelScrolled(sf::Event::MouseWheelScrolled const& mouseScroll);

    static constexpr size_t tileDepth = 7u;

private:
    Game();
    ~Game();

    std::vector<Player> players;
    Board board;
    size_t currentPlayer = 0;
    sf::Vector2f mouseClickPosition;
    bool mouseDragging = false;
};

#endif