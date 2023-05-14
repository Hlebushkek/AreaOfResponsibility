#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include "../include/TextCircle.hpp"

const int BASE_POINT_RADIUS = 8;
const int MAIN_POINT_RADIUS = 12;

const int MAXN = 1000;
const int MAXW = 1000;

int n, W, xa, ya, xb, yb;
int algorithmType;
int x[MAXN + 2], y[MAXN + 2], w[MAXN + 2];
int dp[MAXN + 2][MAXW + 2][2];

struct Line
{
    float k, b;
};

enum SIDE { LEFT, RIGHT, OVERLAY };

SIDE determineSide(sf::Vector2f point, float k, float b)
{
    std::cout << "y = " << k << "x + " << b << std::endl;
    std::cout << "(" << point.x << "," << point.y << ")" << std::endl;

    float line_y = k * point.x + b;

    if (point.y < line_y)
        return SIDE::RIGHT;
    else if (point.y > line_y)
        return SIDE::LEFT;

    return SIDE::OVERLAY;
}

float distance(sf::Vector2f p1, sf::Vector2f p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

sf::Vector2f getRandomPoint(const sf::Vector2u& screenSize, const sf::Vector2u& inset)
{
    return sf::Vector2f(rand() % (screenSize.x - inset.x), rand() % (screenSize.y - inset.y));
}

int calcDiff(const std::vector<TextCircle*>& shapes, float k, float b, SIDE onLineAssign = SIDE::OVERLAY)
{
    int left_sum = 0;
    int right_sum = 0;

    for (auto shape : shapes)
    {
        SIDE side = determineSide(shape->getPosition(), k, b);
        std::cout << "Weight: " << shape->getValue() << "\tside: " << side << std::endl;

        switch (side)
        {
        case LEFT:
            left_sum += shape->getValue();
            break;
        case RIGHT:
            right_sum += shape->getValue();
            break;
        case OVERLAY:
            if (onLineAssign == SIDE::LEFT)
                left_sum += shape->getValue();
            else if (onLineAssign == SIDE::RIGHT)
                right_sum += shape->getValue();
            break;
        }

        std::cout << "Current right: " << right_sum << "\tCurrent left: " << left_sum << std::endl;
    }

    std::cout << "Diff: " << abs(left_sum - right_sum) << std::endl;
    return abs(left_sum - right_sum);
}

Line GreedyAlgoithm(TextCircle *pA, TextCircle *pB, std::vector<TextCircle*>& shapes)
{
    int bestResult = INT_MAX;
    Line bestLine { 0, 0 };

    sf::Vector2f midAB = sf::Vector2f(
        (pA->getPosition().x + pB->getPosition().x) / 2.f,
        (pA->getPosition().y + pB->getPosition().y) / 2.f
    );

    std::cout << "A: " << pA->getPosition().x << " " << pA->getPosition().y << std::endl;
    std::cout << "B: " << pB->getPosition().x << " " << pB->getPosition().y << std::endl;
    std::cout << "Mid AB: " << midAB.x << " " << midAB.y << std::endl;

    for (auto shape : shapes)
    {
        sf::Vector2f pos = shape->getPosition();
        float k = (pos.y - midAB.y) / (pos.x - midAB.x);
        float b = midAB.y - k * midAB.x;
        std::cout << "y = " << k << "x + " << b << std::endl;

        int diff1 = calcDiff(shapes, k, b, SIDE::LEFT);
        int diff2 = calcDiff(shapes, k, b, SIDE::RIGHT);

        int diff = std::min(diff1, diff2);

        if (diff < bestResult)
        {
            bestResult = diff;
            bestLine.k = k;
            bestLine.b = b;
        }
    }

    std::cout << "Best result: " << bestResult <<
        "\tline: y = " << bestLine.k << "x + " << bestLine.b << std::endl;
    return bestLine;
}

int main()
{
    srand((unsigned)time(0)); 

    sf::Vector2u screenSize(720, 480);
    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Coursework");
    std::vector<TextCircle*> shapes;
    
    sf::Vector2u inset(BASE_POINT_RADIUS, BASE_POINT_RADIUS);

    std::cin >> n >> W;

    std::cin >> algorithmType;

    sf::Vector2f a_pos = getRandomPoint(screenSize, inset);
    xa = a_pos.x;
    ya = a_pos.y;
    sf::Vector2f b_pos = getRandomPoint(screenSize, inset);
    xb = b_pos.x;
    yb = b_pos.y;

    TextCircle* pA = new TextCircle(BASE_POINT_RADIUS, 30ULL, 0, "A");
    pA->setPosition(sf::Vector2f(xa, ya));
    pA->setCircleColor(sf::Color::Red);

    TextCircle* pB = new TextCircle(BASE_POINT_RADIUS, 30ULL, 0, "B");
    pB->setPosition(sf::Vector2f(xb, yb));
    pB->setCircleColor(sf::Color::Red);

    for (int i = 0; i < n; i++) {
        w[i] = rand() % (W - 1) + 1;
        TextCircle* shape = new TextCircle(BASE_POINT_RADIUS, 30ULL, w[i]);
        shape->setPosition(getRandomPoint(screenSize, inset));
        shape->setCircleColor(sf::Color::Yellow);
        shapes.push_back(shape);
    }

    Line bestLine { 0, 0 };

    switch (algorithmType)
    {
    case 0: //Greedy algorithm
        bestLine = GreedyAlgoithm(pA, pB, shapes);
    case 1:
        break;
    case 2:
        break;
    default:
        break;
    }

    // sf::VertexArray result_line { sf::Vector2f(), sf::Vector2f() }
    sf::VertexArray result_line(sf::PrimitiveType::Lines, 2);
    result_line[0].position = sf::Vector2f(0, bestLine.b);
    result_line[0].color = sf::Color::Green;
    result_line[1].position = sf::Vector2f(screenSize.x, bestLine.k * screenSize.x + bestLine.b);
    result_line[1].color = sf::Color::Green;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Blue);
        for (auto& shape : shapes)
        {
            window.draw(*pA);
            window.draw(*pB);
            window.draw(*shape);
        }

        window.draw(result_line);
        window.display();
    }

    return 0;
}