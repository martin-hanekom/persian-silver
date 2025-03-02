#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "game.hpp"

int convertPic(std::string const& name);

int main()
{
    std::srand(std::time({}));
    silver::Game::get().run(3u);
    //convertPic("spearman");
    return 0;
}

int convertPic(std::string const& name)
{
    sf::Image image;
    if (!image.loadFromFile("assets/" + name + ".png"))
    {
        return -1;
    }

    sf::Vector2u size = image.getSize();
    for (unsigned int x = 0; x < size.x; ++x)
    {
        for (unsigned int y = 0; y < size.y; ++y)
        {
            if (image.getPixel({x, y}).a > 70)
            {
                image.setPixel({x, y}, sf::Color::White);
            }
        }
    }

    if (!image.saveToFile("assets/" + name + "_white.png"))
    {
        return -1;
    }

    return 0;
}