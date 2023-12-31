#include <SFML/Graphics.hpp>
#include <iostream>

void init(sf::ConvexShape &arrow)
{
    const sf::Vector2f position = {500, 350};
    float rotation = -82;

    arrow.setPointCount(7);
    arrow.setPoint(0, {90, 0});
    arrow.setPoint(1, {30, 60});
    arrow.setPoint(2, {30, 30});
    arrow.setPoint(3, {-30, 30});
    arrow.setPoint(4, {-30, -30});
    arrow.setPoint(5, {30, -30});
    arrow.setPoint(6, {30, -60});
    arrow.setFillColor(sf::Color(0xFF, 0xFF, 0));
    arrow.setPosition(position);
    arrow.setRotation(rotation);
    arrow.setOutlineColor(sf::Color(0x00, 0x00, 0x00));
    arrow.setOutlineThickness(3);
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        defaut:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &arrow)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(arrow);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 1000;
    constexpr unsigned WINDOW_HEIGHT = 700;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Yellow arrow", sf::Style::Default, settings);

    sf::ConvexShape arrow;

    init(arrow);

    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, arrow);
    }
}