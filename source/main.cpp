#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include "Line.hpp"
#include "Utils.hpp"
#include "DislocationPoint.hpp"
#include "TextCircle.hpp"
#include "GreedyAlgorithmSolver.hpp"
#include "GeneticAlgorithmSolver.hpp"
#include "GeneticAlgorithmAdvancedSolver.hpp"
#include "DynamicProgrammingSolver.hpp"

int main()
{
    srand((unsigned)time(0));

    int n, W;
    int algorithmType; 

    sf::Vector2u screenSize(720, 480);
    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Coursework");
    
    sf::Vector2u inset(BASE_POINT_RADIUS, BASE_POINT_RADIUS);

    std::cout << "Enter number of points:\n";
    std::cin >> n;
    std::cout << "Enter max weight:\n";
    std::cin >> W;
    std::cout << "Enter algorithm (0 - Greedy, 1 - Genetic, 2 - Advanced Genetic, 3 - Recursive):\n";
    std::cin >> algorithmType;

    sf::Vector2f a_pos = getRandomPoint(screenSize, inset);
    sf::Vector2f b_pos = getRandomPoint(screenSize, inset);

    std::vector<DislocationPoint> models;
    std::vector<TextCircle> shapes;

    DislocationPoint aModel = DislocationPoint(a_pos, 0, "A", DislocationPoint::PointType::A);
    DislocationPoint bModel = DislocationPoint(b_pos, 0, "B", DislocationPoint::PointType::B);
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

    Solver* solver = nullptr;

    switch (algorithmType)
    {
    case 0:
        solver = new GreedyAlgorithmSolver();
        break;
    case 1:
        solver = new GeneticAlgorithmSolver();
        break;
    case 2:
        solver = new GeneticAlgorithmAdvancedSolver();
        break;
    case 3:
        solver = new DynamicProgrammingSolver();
        break;
    default:
        break;
    }

    Line bestLine = solver->solve(aModel, bModel, models);

    sf::VertexArray result_line(sf::PrimitiveType::Lines, 2);
    result_line[0].position = sf::Vector2f(0, bestLine.b());
    result_line[0].color = sf::Color::Red;
    result_line[1].position = sf::Vector2f(screenSize.x, bestLine.k() * screenSize.x + bestLine.b());
    result_line[1].color = sf::Color::Red;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        for (auto& shape : shapes)
            window.draw(shape);

        window.draw(result_line);
        window.display();
    }

    return 0;
}