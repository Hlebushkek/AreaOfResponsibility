#include <iostream>
#include "AORMath.hpp"
#include "Line.hpp"
#include "DislocationPoint.hpp"
#include "GreedyAlgorithmSolver.hpp"

Line GreedyAlgorithmSolver::solve(DislocationPoint& pA, DislocationPoint& pB, std::vector<DislocationPoint>& points)
{
    int bestResult = INT_MAX;
    Line bestLine;

    sf::Vector2f midAB = sf::Vector2f(
        (pA.getPosition().x + pB.getPosition().x) / 2.f,
        (pA.getPosition().y + pB.getPosition().y) / 2.f
    );

    for (auto point : points)
    {
        sf::Vector2f pos = point.getPosition();
        Line line(midAB, pos);

        int diff1 = AORMath::calcDiff(points, line, SIDE::LEFT);
        int diff2 = AORMath::calcDiff(points, line, SIDE::RIGHT);

        int diff = std::min(diff1, diff2);

        if (diff < bestResult)
        {
            bestResult = diff;
            bestLine = line;
        }
    }
    
    return bestLine;
}