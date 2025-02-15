#include <SFML/Graphics.hpp>
#include "game.hpp"

int main()
{
    auto& game = Game::get();
    game.run();
    return 0;
}

