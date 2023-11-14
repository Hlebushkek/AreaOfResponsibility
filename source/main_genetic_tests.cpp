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

    n = 50;
    W = 10;
    float mrs[] = {0.2f, 0.4f, 0.6f, 0.8f};

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

    std::shared_ptr<Solver> solver;
    std::shared_ptr<Solver> advancedSolver;
    Line bestLine;

    std::ofstream file("../resources/output.csv");
    std::ofstream fileRes("../resources/outputRes.csv");
    file << "mr, genetic, advanced_genetic\n";
    fileRes << "mr, genetic, advanced_genetic\n";

    for (float mr: mrs)
    {
        float resSum = 0;
        float timeSum = 0;

        float resAdvancedSum = 0;
        float timeAdvancedSum = 0;

        solver = std::make_shared<GeneticAlgorithmSolver>(mr);
        for (int i = 0; i < 20; i++)
        {
            std::cout << "\nTest set: " << mr << " " << i << std::endl;

            Timer t;
            bestLine = solver->solve(aModel, bModel, models);
            float time = t.elapsed();
            std::cout << "Time elapsed: " << time << std::endl;
            std::cout << "Line: " << bestLine << std::endl;

            int result = std::min(
                AORMath::calcDiff(models, bestLine, SIDE::LEFT),
                AORMath::calcDiff(models, bestLine, SIDE::RIGHT)
            );
            std::cout << "Result: " << result << std::endl;
            // std::cout << "E: " << (float)result / sum * 100.f << "%" << std::endl;
            resSum += result;
            timeSum += time;
        }

        advancedSolver = std::make_shared<GeneticAlgorithmAdvancedSolver>(mr);
        for (int i = 0; i < 20; i++)
        {
            std::cout << "\nAdvanced test set: " << mr << " " << i << std::endl;

            Timer t;
            bestLine = advancedSolver->solve(aModel, bModel, models);
            float time = t.elapsed();
            std::cout << "Time elapsed: " << time << std::endl;
            std::cout << "Line: " << bestLine << std::endl;

            int result = std::min(
                AORMath::calcDiff(models, bestLine, SIDE::LEFT),
                AORMath::calcDiff(models, bestLine, SIDE::RIGHT)
            );
            std::cout << "Advanced result: " << result << std::endl;
            // std::cout << "E: " << (float)result / sum * 100.f << "%" << std::endl;
            resAdvancedSum += result;
            timeAdvancedSum += time;
        }

        file << mr;
        {
            float avg = timeSum / 20;
            std::cout << solver->getName() << " average time: " << avg << std::endl;
            float advacnedAvg = timeAdvancedSum / 20;
            std::cout << advancedSolver->getName() << " average advanced time: " << avg << std::endl;
            file << ", " << avg << ", " << advacnedAvg;
        }
        file << "\n";

        fileRes << mr << ", " << resSum / sum / 20.f * 100.f << ", " << resAdvancedSum / sum / 20.f * 100.f << "\n";
    }

    file.close();
    fileRes.close();

    system("py ../resources/plot.py ../resources/output.csv genetic 0");
    system("py ../resources/plot.py ../resources/outputRes.csv genetic 1");

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

        window.clear(sf::Color::Black);
        for (auto& shape : shapes)
            window.draw(shape);

        window.draw(result_line);
        window.display();
    }

    return 0;
}