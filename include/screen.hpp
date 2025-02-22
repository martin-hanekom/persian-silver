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
    static void draw(sf::Drawable const& drawable);

    void setMainView();
    void setUIView();

    void zoom(float factor);
    void pan(sf::Vector2f offset);
    sf::Vector2f mainViewCoords(sf::Vector2i pixels) const;
    sf::Vector2f uiViewCoords(sf::Vector2i pixels) const;

    enum class Corner
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
    };

    template <Corner corner>
    static constexpr sf::Vector2f getCornerOffset()
    {
        switch (corner)
        {
            case Screen::Corner::TopLeft:
                return {-(windowSize.x / 2.f), -(windowSize.y / 2.f)};
            case Screen::Corner::TopRight:
                return {windowSize.x / 2.f, -(windowSize.y / 2.f)};
            case Screen::Corner::BottomLeft:
                return {-(windowSize.x / 2.f), windowSize.y / 2.f};
            case Screen::Corner::BottomRight:
                return {windowSize.x / 2.f, windowSize.y / 2.f};
            default:
                return {0.f, 0.f};
        }
    }


private:
    Screen();
    ~Screen();

    static constexpr sf::Vector2u windowSize{1920u, 1080u};
    static constexpr char const* title{"Persian Silver"};
    static constexpr float defaultZoom = 3.f;

    sf::RenderWindow window{sf::VideoMode(windowSize), "Persian Silver", sf::State::Fullscreen};
    sf::View mainView{{0.f, 0.f}, sf::Vector2f(windowSize)};
    sf::View uiView{{0.f, 0.f}, sf::Vector2f(windowSize)};
};

#endif