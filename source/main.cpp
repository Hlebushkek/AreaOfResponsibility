#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
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
    int WTestSet[] = {10, 20, 50, 100};

    std::vector<DislocationPoint> models;
    std::vector<TextCircle> shapes;
    Solver* solvers[] = { new GreedyAlgorithmSolver(), new GeneticAlgorithmSolver(), new DynamicProgrammingSolver()};

    Line bestLine;

    for (int n: nTestSet)
    {
        for (int W: WTestSet)
        {
            std::cout << "\nTest set: " << n << " " << W << std::endl;

            models.clear();
            shapes.clear();

            sf::Vector2f a_pos = getRandomPoint(screenSize, inset);
            sf::Vector2f b_pos = getRandomPoint(screenSize, inset);

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

            for (auto& solver : solvers)
            {
                Timer t;
                bestLine = solver->solve(aModel, bModel, models);
                std::cout << "Time elapsed: " << t.elapsed() << std::endl;
                std::cout << "Line: " << bestLine << std::endl; 
                std::cout << "Result: " << std::min(
                    AORMath::calcDiff(models, bestLine, SIDE::LEFT),
                    AORMath::calcDiff(models, bestLine, SIDE::RIGHT)
                ) << std::endl; 
            }
        }
    }

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