#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <cassert>

using namespace std;

struct Shape
{
    sf::RectangleShape rect;
    int width;
    int height;
    float speed = 50;
    sf::Vector2f position;
};

struct PRNG
{
    mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    // Создаём псевдо-устройство для получения случайного зерна.
    random_device device;
    // Получаем случайное зерно последовательности
    generator.engine.seed(device());
}

float random(float minValue, float maxValue)
{
    PRNG generator;
    initGenerator(generator);
    assert(minValue < maxValue);
    uniform_real_distribution<float> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

// sf::Vector2f toEuclidean(float radius, float angle)
// {
//     return {
//         radius * (float)cos(angle),
//         radius * (float)sin(angle)};
// }

// float toDegress(float radians)
// {
//     return float(double(radians) * 180.0 / M_PI);
// }

void updateShapeElements(Shape &shape)
{
    shape.rect.setPosition(shape.position);

    // const sf::Vector2f pupilRotationOffset = toEuclidean(40, eye.pupilRotation);

    // if (pow(mousePosition.x - eye.position.x, 2) + pow(mousePosition.y - eye.position.y, 2) <= 40 * 40)
    // {
    //     eye.pupil.setPosition(mousePosition);
    // }
    // else
    // {
    //     eye.pupil.setPosition(eye.position + pupilRotationOffset);
    // }
}

void initShape(Shape &shape)
{
    const float minWidthShape = 10;
    const float maxWidthShape = 100;
    float rectWidth = random(minWidthShape, maxWidthShape);
    const float minHeightShape = 10;
    const float maxHeightShape = 100;

    float rectHeight = random(minHeightShape, maxHeightShape);
    float x = random(0, 800);
    cout << rectWidth << ' ' << rectHeight << ' ' << x << endl;
    shape.position = {x, -maxHeightShape};
    shape.rect.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    shape.rect.setSize({rectWidth, rectHeight});

    updateShapeElements(shape);
}

// float onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
// {
//     mousePosition = {float(event.x), float(event.y)};
// }

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
        default:
            break;
        }
    }
}

void update(sf::Clock &clock, Shape &shape)
{
    // const sf::Vector2f delta = mousePosition - eye.position;
    // shape.pupilRotation = atan2(delta.y, delta.x);
    float dt = clock.restart().asSeconds();
    shape.position.y += shape.speed * dt;
    updateShapeElements(shape);
}

void redrawFrame(sf::RenderWindow &window, Shape &shape)
{
    window.clear();
    window.draw(shape.rect);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Tetris 0.0", sf::Style::Default, settings);

    sf::Clock clock;
    Shape shape;

    initShape(shape);

    while (window.isOpen())
    {
        pollEvents(window);
        update(clock, shape);
        redrawFrame(window, shape);
    }
}