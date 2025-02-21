#ifndef PERSIAN_SILVER_GAME_HPP
#define PERSIAN_SILVER_GAME_HPP

#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "board.hpp"
#include "player.hpp"
#include "ui.hpp"
#include "action.hpp"

class Game
{
public:
    Game(Game const&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game const&) = delete;
    Game& operator=(Game&&) = delete;

    static Game& get();

    void run(size_t playerCount);
    void drawMain() const;
    void drawUI() const;
    void onClosed();
    void onKeyPressed(sf::Event::KeyPressed const& keyPressed);
    void onMouseMoved(sf::Event::MouseMoved const& mouseMove);
    void onMouseButtonPressed(sf::Event::MouseButtonPressed const& mouseButton);
    void onMouseWheelScrolled(sf::Event::MouseWheelScrolled const& mouseScroll);

    static void submit(MoveAction&& action);

    void nextPlayer();
    bool isCurrentPlayerPiece(Piece const& piece) const;

    static constexpr size_t tileDepth = 7u;

private:
    Game();
    ~Game();

    Screen& screen;
    std::vector<Player> players;
    Board board;
    Button nextButton;
    sf::Text banner;

    size_t currentPlayer = 0;
    sf::Vector2f mouseClickPosition;
    bool mouseDragging = false;
};

#endif