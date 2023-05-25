#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "AORMath.hpp"
#include "Line.hpp"
#include "DislocationPoint.hpp"
#include "GeneticAlgorithmSolver.hpp"

const int POPULATION_SIZE = 100;
const float SELECTION_RATE = 0.2;
const int MAX_GENERATIONS = 1000;
const float MUTATION_RATE = 0.6;

bool areAllValuesSimilar(std::vector<int>& values) {
    for (int i = 1; i < values.size(); i++)
        if (values[i] != values[0])
            return false;
    
    return true;
}

void printLines(std::vector<Line>& lines)
{
    for (auto& line : lines)
        std::cout << "StartPoint=(" << line.startPoint.x << "," << line.startPoint.y <<
            "\tEndPoint=(" << line.endPoint.x << "," << line.endPoint.y << std::endl;
}

Line GeneticAlgorithmSolver::solve(DislocationPoint& pA, DislocationPoint& pB, std::vector<DislocationPoint>& points)
{
    Line abLine(pA.getPosition(), pB.getPosition());
    Line bestLine;
    int bestResult = INT_MAX;

    std::vector<Line> population = generatePopulation(pA, pB);

    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        // printLines(population);
        std::vector<int> fitnessValues(POPULATION_SIZE);
        for (int i = 0; i < POPULATION_SIZE; i++)
            fitnessValues[i] = AORMath::calcDiff(points, population[i], SIDE::LEFT);

        if (areAllValuesSimilar(fitnessValues))
        {
            population = generatePopulation(pA, pB);
            continue;
        }

        int N = POPULATION_SIZE * SELECTION_RATE;
        std::partial_sort(population.begin(), population.begin() + N, population.end(),
            [&population, &fitnessValues](const Line& obj1, const Line& obj2) {
            int index1 = std::distance(population.begin(), std::find(population.begin(), population.end(), obj1));
            int index2 = std::distance(population.begin(), std::find(population.begin(), population.end(), obj2));
            return fitnessValues[index1] < fitnessValues[index2];
        });
        
        std::vector<Line> bestLines(population.begin(), population.begin() + N);

        std::vector<Line> offspring;
        for (int i = 0; i < POPULATION_SIZE; i++) {
            int parentIndex1 = rand() % POPULATION_SIZE * SELECTION_RATE;
            int parentIndex2 = rand() % POPULATION_SIZE * SELECTION_RATE;
            const Line& parent1 = bestLines[parentIndex1];
            const Line& parent2 = bestLines[parentIndex2];

            Line child = crossover(parent1, parent2, abLine);

            mutate(child, abLine);

            offspring.push_back(child);
        }

        population = offspring;

        int bestFitness = AORMath::calcDiff(points, bestLines[0], SIDE::LEFT);
        if (bestFitness < bestResult)
        {
            bestResult = bestFitness;
            bestLine = bestLines[0];
        }
        
        // std::cout << "StartPoint=(" << bestLines[0].startPoint.x << "," << bestLines[0].startPoint.y <<
        //     "\tEndPoint=(" << bestLines[0].endPoint.x << "," << bestLines[0].endPoint.y <<  ") Best Fitness: " << bestFitness << std::endl;

        if (bestResult == 0)
            break;
    }
    
    // std::cout << "Best result: " << bestResult << "\nWith line: y = " << bestLine.k() << "x + " << bestLine.b() << std::endl;
    return bestLine;
}

std::vector<Line> GeneticAlgorithmSolver::generatePopulation(DislocationPoint& pA, DislocationPoint& pB)
{
    Line abLine(pA.getPosition(), pB.getPosition());
    
    std::vector<Line> population(POPULATION_SIZE);
    for (int i = 0; i < POPULATION_SIZE; i++) {
        sf::Vector2f startPoint = abLine.getPointOnLineSegment(pA.getPosition().x, pB.getPosition().x);
        sf::Vector2f endPoint = sf::Vector2f(static_cast<float>(rand()) / RAND_MAX * 720, static_cast<float>(rand()) / RAND_MAX * 480);
        population[i] = Line(startPoint, endPoint);
    }

    return population;
}

void GeneticAlgorithmSolver::mutate(Line &line, Line &abLine)
{
    if (static_cast<float>(rand()) / RAND_MAX < MUTATION_RATE)
    {
        line.startPoint = abLine.randomlyMovePointAlongLine(
            line.startPoint, (static_cast<float>(rand()) / RAND_MAX - 0.5f),
            abLine.startPoint.x, abLine.endPoint.x
        );

        line.endPoint.x += (static_cast<float>(rand()) / RAND_MAX - 0.5f);
        line.endPoint.y += (static_cast<float>(rand()) / RAND_MAX - 0.5f);
    }
}

Line GeneticAlgorithmSolver::crossover(const Line &parent1, const Line &parent2, Line& abLine)
{
    Line offspring;
    float crossoverPoint = static_cast<float>(rand()) / RAND_MAX;

    float startX = parent1.startPoint.x + crossoverPoint * (parent2.startPoint.x - parent1.startPoint.x);
    offspring.startPoint = sf::Vector2f(startX, abLine.k() * startX + abLine.b());

    offspring.endPoint.x = parent1.endPoint.x + crossoverPoint * (parent2.endPoint.x - parent1.endPoint.x);
    offspring.endPoint.y = parent1.endPoint.y + crossoverPoint * (parent2.endPoint.y - parent1.endPoint.y);

    return offspring;
}

std::string GeneticAlgorithmSolver::getName()
{
    return "Genetic Algorithm";
}
