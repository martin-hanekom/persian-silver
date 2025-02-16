#ifndef PERSIAN_SILVER_SCREEN_HPP
#define PERSIAN_SILVER_SCREEN_HPP

#include <SFML/Graphics.hpp>

class Screen
{
public:
    Screen(Screen const&) = delete;
    Screen(Screen&&) = delete;
    Screen& operator=(Screen const&) = delete;
    Screen& operator=(Screen&&) = delete;

    static Screen& get();
    static sf::RenderWindow& getWindow();
    static sf::Font& getFont();
    static void draw(sf::Drawable const& drawable);

    void zoom(float factor);
    void pan(sf::Vector2f offset);
    sf::Vector2f mapPixelToCoords(sf::Vector2i pixels) const;

private:
    Screen();
    ~Screen();

    static constexpr sf::Vector2u windowSize{1920u, 1080u};
    static constexpr char const* title{"Persian Silver"};
    static constexpr float defaultZoom = 3.f;

    sf::RenderWindow window{sf::VideoMode(windowSize), "Persian Silver", sf::State::Fullscreen};
};

#endif