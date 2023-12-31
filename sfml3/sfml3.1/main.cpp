#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

void init(sf::ConvexShape &pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {-20, -20});
    pointer.setPoint(2, {-20, 20});
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x),
                     float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        defaut:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, sf::Clock &clock, sf::ConvexShape &pointer)
{
    const float speed = 15;
    const float dt = clock.restart().asSeconds();
    const float maxRotation = speed * dt;

    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    const float angle = atan2(delta.y, delta.x);

    const float pointerRotation = pointer.getRotation();
    float deltaAngle = toDegrees(angle) - pointerRotation;

    if (deltaAngle > 180)
    {
        deltaAngle -= 360;
    }
    else if (deltaAngle < -180)
    {
        deltaAngle += 360;
    }

    deltaAngle = std::max(-maxRotation, std::min(deltaAngle, maxRotation));

    pointer.setRotation(pointerRotation + deltaAngle);
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                            "Pointer follows mouse", sf::Style::Default, settings);

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;
    sf::Clock clock;

    init(pointer);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, clock, pointer);
        redrawFrame(window, pointer);
    }
}