#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include "Line.hpp"
#include "DislocationPoint.hpp"
#include "TextCircle.hpp"
#include "Timer.hpp"
#include "AORMath.hpp"
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

    int nTestSet[] = {5, 50, 100, 500};
    W = 10;

    std::vector<DislocationPoint> models;
    std::vector<TextCircle> shapes;

    std::vector<std::pair<Solver*, float>> solvers = {
        {new GreedyAlgorithmSolver(), 0.f},
        {new GeneticAlgorithmSolver(), 0.f},
        {new DynamicProgrammingSolver(), 0.f}
    };

    Line bestLine;

    std::ofstream file("../resources/output.csv");
    std::ofstream fileRes("../resources/outputRes.csv");
    file << "n, greedy, genetic, recursive\n";
    fileRes << "n, greedy, genetic, recursive\n";

    for (int n: nTestSet)
    {
        float greedyResultSum = 0;
        float geneticResultSum = 0;
        float recursiveResultSum = 0;

        for (int i = 0; i < 20; i++)
        {
            std::cout << "\nTest set: " << n << " " << i << std::endl;

            models.clear();
            shapes.clear();

            sf::Vector2f a_pos = getRandomPoint(screenSize, inset);
            sf::Vector2f b_pos = getRandomPoint(screenSize, inset);

            DislocationPoint aModel = DislocationPoint(a_pos, 0, "A", true);
            DislocationPoint bModel = DislocationPoint(b_pos, 0, "B", true);
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
                if (solver->getName() == "Greedy Algorithm")
                    greedyResultSum += (float)result / sum * 100.f;
                else if (solver->getName() == "Genetic Algorithm")
                    geneticResultSum += (float)result / sum * 100.f;
                else if (solver->getName() == "Recursive Algorithm")
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
        float avgRecursive = recursiveResultSum / 20.f;
        fileRes << n << ", " << avgGreedy << ", " << avgGenetic << ", " << avgRecursive << "\n";
    }

    file.close();
    fileRes.close();

    system("py ../resources/plot.py ../resources/output.csv 0");
    system("py ../resources/plot.py ../resources/outputRes.csv 1");

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