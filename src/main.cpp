#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "game.hpp"

int main()
{
    std::srand(std::time({}));
    auto& game = Game::get();
    game.run();
    return 0;
}

