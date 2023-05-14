#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include "../include/TextCircle.hpp"

const int BASE_POINT_RADIUS = 8;
const int MAIN_POINT_RADIUS = 12;

const int MAXN = 1000;
const int MAXW = 1000;

int n, W, xa, ya, xb, yb;
int x[MAXN + 2], y[MAXN + 2], w[MAXN + 2];
int dp[MAXN + 2][MAXW + 2][2];

sf::Vector2f getRandomPoint(const sf::Vector2u& screenSize, const sf::Vector2u& inset)
{
    return sf::Vector2f(rand() % (screenSize.x - inset.x), rand() % (screenSize.y - inset.y));
}

int main()
{
    srand((unsigned)time(0)); 

    sf::Vector2u screenSize(480, 360);
    sf::RenderWindow window(sf::VideoMode(screenSize), "Coursework");
    std::vector<TextCircle> shapes;
    
    sf::Vector2u inset(BASE_POINT_RADIUS, BASE_POINT_RADIUS);

    std::cin >> n >> W;

    sf::Vector2f a_pos = getRandomPoint(screenSize, inset);
    xa = a_pos.x;
    ya = a_pos.y;
    sf::Vector2f b_pos = getRandomPoint(screenSize, inset);
    xb = b_pos.x;
    yb = b_pos.y;

    TextCircle pA("A", BASE_POINT_RADIUS);
    pA.setPosition(sf::Vector2f(xa, ya));
    pA.setCircleColor(sf::Color::Red);
    shapes.push_back(pA);

    TextCircle pB("B", BASE_POINT_RADIUS);
    pB.setPosition(sf::Vector2f(xb, yb));
    pB.setCircleColor(sf::Color::Red);
    shapes.push_back(pB);

    for (int i = 1; i <= n; i++) {
        // std::cin >> x[i] >> y[i] >> w[i];
        w[i] = rand() % 10;
        TextCircle shape(std::to_string(w[i]), BASE_POINT_RADIUS);
        shape.setCircleColor(sf::Color::Yellow);
        shape.setPosition(getRandomPoint(screenSize, inset));
        shapes.push_back(shape);
    }

    x[0] = xa; y[0] = ya; w[0] = 0;
    x[n + 1] = xb; y[n + 1] = yb; w[n + 1] = 0;
    std::sort(x, x + n + 2);
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= W; j++) {
            dp[i][j][0] = dp[i][j][1] = 1e9;
        }
    }
    dp[0][0][0] = dp[0][0][1] = 0;
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j <= W; j++) {
            for (int k = 0; k < i; k++) {
                int dist = x[i] - x[k];
                int wsum = 0;
                for (int l = k + 1; l < i; l++) {
                    wsum += w[l];
                }
                dp[i][j][0] = std::min(dp[i][j][0], dp[k][j - wsum][1] + dist * std::max(0, wsum - j));
                dp[i][j][1] = std::min(dp[i][j][1], dp[k][j - wsum][0] + dist * std::max(0, wsum - j));
            }
        }
    }
    int ans = 1e9;
    for (int j = 0; j <= W; j++) {
        ans = std::min(ans, dp[n + 1][j][0]);
        ans = std::min(ans, dp[n + 1][j][1]);
    }
    std::cout << ans << std::endl;

    double k = (double)(yb - ya) / (double)(xb - xa);
    double b = ya - k * xa;
    std::cout << "y = " << k << "x + " << b << std::endl;

    // sf::VertexArray result_line { sf::Vector2f(), sf::Vector2f() }
    sf::VertexArray result_line(sf::PrimitiveType::Lines, 2);
    result_line[0].position = sf::Vector2f(0, b);
    result_line[0].color = sf::Color::Green;
    result_line[1].position = sf::Vector2f(screenSize.x, k * screenSize.x + b);
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
            window.draw(shape);

        window.draw(result_line);
        window.display();
    }

    return 0;
}