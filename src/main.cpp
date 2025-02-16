#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "game.hpp"

///*
int main()
{
    std::srand(std::time({}));
    auto& game = Game::get();
    game.run(3u);
    return 0;
}

/*
int main()
{
 sf::Image image;
    if (!image.loadFromFile("assets/man.png"))
    {
        return -1;
    }

    sf::Vector2u size = image.getSize();
    for (unsigned int x = 0; x < size.x; ++x)
    {
        for (unsigned int y = 0; y < size.y; ++y)
        {
            if (image.getPixel({x, y}).a   != 0)
            {
                image.setPixel({x, y}, sf::Color::White);
            }
        }
    }

    if (!image.saveToFile("assets/man_white.png"))
    {
        return -1;
    }

    return 0;
}
    /**/