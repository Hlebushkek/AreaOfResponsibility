#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include "Line.hpp"
#include "DislocationPoint.hpp"
#include "TextCircle.hpp"
#include "GreedyAlgorithmSolver.hpp"
#include "GeneticAlgorithmSolver.hpp"
#include "DynamicProgrammingSolver.hpp"

const int BASE_POINT_RADIUS = 8;

const int MAXN = 1000;
const int MAXW = 1000;

int n, W;
int algorithmType;

sf::Vector2f getRandomPoint(const sf::Vector2u& screenSize, const sf::Vector2u& inset)
{
    return sf::Vector2f(rand() % (screenSize.x - inset.x), rand() % (screenSize.y - inset.y));
}

int main()
{
    srand((unsigned)time(0)); 

    sf::Vector2u screenSize(720, 480);
    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Coursework");
    
    sf::Vector2u inset(BASE_POINT_RADIUS, BASE_POINT_RADIUS);

    std::cin >> n >> W;
    std::cin >> algorithmType;

    sf::Vector2f a_pos = getRandomPoint(screenSize, inset);
    sf::Vector2f b_pos = getRandomPoint(screenSize, inset);

    std::vector<DislocationPoint> models;
    std::vector<TextCircle> shapes;

    DislocationPoint aModel = DislocationPoint(a_pos, 0, "A", true);
    DislocationPoint bModel = DislocationPoint(b_pos, 0, "B", true);
    models.push_back(aModel);
    models.push_back(bModel);

    for (size_t i = 0; i < n; i++)
    {
        int w = rand() % (W - 1) + 1;
        sf::Vector2f pos = getRandomPoint(screenSize, inset);
        models.push_back(DislocationPoint(pos, w));
    }

    for (size_t i = 0; i < models.size(); i++)
    {
        TextCircle shape = TextCircle(&models[i], BASE_POINT_RADIUS);
        shapes.push_back(shape);
    }

    Solver* solver;

    switch (algorithmType)
    {
    case 0:
        solver = new GreedyAlgorithmSolver();
        break;
    case 1:
        solver = new GeneticAlgorithmSolver();
        break;
    case 2:
        solver = new DynamicProgrammingSolver();
        break;
    default:
        break;
    }

    Line bestLine = solver->solve(aModel, bModel, models);

    sf::VertexArray result_line(sf::PrimitiveType::Lines, 2);
    result_line[0].position = sf::Vector2f(0, bestLine.b());
    result_line[0].color = sf::Color::Green;
    result_line[1].position = sf::Vector2f(screenSize.x, bestLine.k() * screenSize.x + bestLine.b());
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