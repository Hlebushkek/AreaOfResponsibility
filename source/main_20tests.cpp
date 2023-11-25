#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <fstream>
#include <cmath>
#include "Line.hpp"
#include "Timer.hpp"
#include "Utils.hpp"
#include "AORMath.hpp"
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

    n = 20;
    W = 10;

    std::vector<DislocationPoint> models;
    std::vector<TextCircle> shapes;

    sf::Vector2f a_pos = getRandomPoint(screenSize, inset);
    sf::Vector2f b_pos = getRandomPoint(screenSize, inset);

    DislocationPoint aModel = DislocationPoint(a_pos, 0, "A", DislocationPoint::PointType::A);
    DislocationPoint bModel = DislocationPoint(b_pos, 0, "B", DislocationPoint::PointType::B);
    models.push_back(aModel);
    models.push_back(bModel);

    int sum = 0;
    for (size_t j = 0; j < n; j++)
    {
        int w = rand() % (W - 1) + 1;
        sf::Vector2f pos = getRandomPoint(screenSize, inset);
        models.push_back(DislocationPoint(pos, w));
        sum += w;
    }

    for (size_t j = 0; j < models.size(); j++)
    {
        TextCircle shape = TextCircle(&models[j], BASE_POINT_RADIUS);
        shapes.push_back(shape);
    }

    std::vector<std::shared_ptr<Solver>> solvers = {
        std::make_shared<GreedyAlgorithmSolver>(),
        std::make_shared<GeneticAlgorithmSolver>(),
        std::make_shared<GeneticAlgorithmAdvancedSolver>(),
        std::make_shared<DynamicProgrammingSolver>()
    };

    Line bestLine;

    int result = std::min(
        AORMath::calcDiff(models, bestLine, SIDE::LEFT),
        AORMath::calcDiff(models, bestLine, SIDE::RIGHT)
    );

    std::cout << "Result: " << result << std::endl;

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
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            bestLine = solvers[0]->solve(aModel, bModel, models);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            bestLine = solvers[1]->solve(aModel, bModel, models);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            bestLine = solvers[2]->solve(aModel, bModel, models);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
            bestLine = solvers[3]->solve(aModel, bModel, models);

        result_line[0].position = sf::Vector2f(0, bestLine.b());
        result_line[1].position = sf::Vector2f(screenSize.x, bestLine.k() * screenSize.x + bestLine.b());

        window.clear(sf::Color::White);
        for (auto& shape : shapes)
            window.draw(shape);

        window.draw(result_line);
        window.display();
    }

    return 0;
}