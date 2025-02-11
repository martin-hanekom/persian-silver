#include <SFML/Graphics.hpp>
#include "board.hpp"
#include "screen.hpp"

int main()
{
    Screen::init();
    Board board(3u);
    sf::View view({0.f, 0.f}, {1920.f, 1080.f});

    while (Screen::isOpen())
    {
        Screen::handleEvents();

        Screen::clear();
        board.draw();
        Screen::display();
    }

    return 0;
}

