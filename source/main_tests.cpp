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

    int nTestSet[] = {5, 50, 100, 250};
    W = 10;

    std::vector<DislocationPoint> models;
    std::vector<TextCircle> shapes;

    std::vector<std::pair<std::shared_ptr<Solver>, float>> solvers = {
        {std::make_shared<GreedyAlgorithmSolver>(), 0.f},
        {std::make_shared<GeneticAlgorithmSolver>(), 0.f},
        {std::make_shared<GeneticAlgorithmAdvancedSolver>(), 0.f},
        {std::make_shared<DynamicProgrammingSolver>(), 0.f}
    };

    Line bestLine;

    std::ofstream file("../resources/output.csv");
    std::ofstream fileRes("../resources/outputRes.csv");
    file << "n, greedy, genetic, advanced_genetic, recursive\n";
    fileRes << "n, greedy, genetic, advanced_genetic, recursive\n";

    for (int n: nTestSet)
    {
        float greedyResultSum = 0;
        float geneticResultSum = 0;
        float advancedGeneticResultSum = 0;
        float recursiveResultSum = 0;

        for (int i = 0; i < 20; i++)
        {
            std::cout << "\nTest set: " << n << " " << i << std::endl;

            models.clear();
            shapes.clear();

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
            
            for (auto& [solver, timeSum] : solvers)
            {
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
                if (std::dynamic_pointer_cast<GreedyAlgorithmSolver>(solver) != nullptr)
                    greedyResultSum += (float)result / sum * 100.f;
                else if (std::dynamic_pointer_cast<GeneticAlgorithmSolver>(solver) != nullptr)
                    geneticResultSum += (float)result / sum * 100.f;
                else if (std::dynamic_pointer_cast<GeneticAlgorithmAdvancedSolver>(solver) != nullptr)
                    advancedGeneticResultSum += (float)result / sum * 100.f;
                else if (std::dynamic_pointer_cast<DynamicProgrammingSolver>(solver) != nullptr)
                    recursiveResultSum += (float)result / sum * 100.f;
                timeSum += time;
            }
        }

        file << n;
        {
            for (auto& [solver, timeSum] : solvers)
            {
                float avg = timeSum / 20.f;
                std::cout << solver->getName() << " average time: " << avg << std::endl;
                file << ", " << avg;
                timeSum = 0;
            }
        }
        file << "\n";

        float avgGreedy = greedyResultSum / 20.f;
        float avgGenetic = geneticResultSum / 20.f;
        float avgAdvancedGenetic = advancedGeneticResultSum / 20.f;
        float avgRecursive = recursiveResultSum / 20.f;
        fileRes << n << ", " << avgGreedy << ", " << avgGenetic << ", "<< avgAdvancedGenetic << ", " << avgRecursive << "\n";
    }

    file.close();
    fileRes.close();

    system("py ../resources/plot.py ../resources/output.csv all 0");
    system("py ../resources/plot.py ../resources/outputRes.csv all 1");
    //system("py ../resources/plot.py ../resources/outputRes.csv genetic 0");
    //system("py ../resources/plot.py ../resources/outputRes.csv genetic 1");

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