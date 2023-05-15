#include <iostream>
#include "AORMath.hpp"
#include "Line.hpp"
#include "DislocationPoint.hpp"
#include "GreedyAlgorithmSolver.hpp"

Line GreedyAlgorithmSolver::solve(DislocationPoint& pA, DislocationPoint& pB, std::vector<DislocationPoint>& points)
{
    int bestResult = INT_MAX;
    Line bestLine { 0, 0 };

    sf::Vector2f midAB = sf::Vector2f(
        (pA.getPosition().x + pB.getPosition().x) / 2.f,
        (pA.getPosition().y + pB.getPosition().y) / 2.f
    );

    for (auto point : points)
    {
        sf::Vector2f pos = point.getPosition();
        float k = (pos.y - midAB.y) / (pos.x - midAB.x);
        float b = midAB.y - k * midAB.x;
        Line line { k, b };
        std::cout << "y = " << line.k << "x + " << line.b << std::endl;

        int diff1 = calcDiff(points, line, SIDE::LEFT);
        int diff2 = calcDiff(points, line, SIDE::RIGHT);

        int diff = std::min(diff1, diff2);

        if (diff < bestResult)
        {
            bestResult = diff;
            bestLine = line;
        }
    }

    std::cout << "Best result: " << bestResult <<
        "\tline: y = " << bestLine.k << "x + " << bestLine.b << std::endl;

    this->bestLine = bestLine;
    
    return bestLine;
}

int GreedyAlgorithmSolver::calcDiff(std::vector<DislocationPoint> &points, Line line, SIDE onLineAssign)
{
    int left_sum = 0;
    int right_sum = 0;

    for (auto point : points)
    {
        SIDE side = determineSide(point.getPosition(), line);

        switch (side)
        {
        case LEFT:
            left_sum += point.getIntValue();
            break;
        case RIGHT:
            right_sum += point.getIntValue();
            break;
        case OVERLAY:
            if (onLineAssign == SIDE::LEFT)
                left_sum += point.getIntValue();
            else if (onLineAssign == SIDE::RIGHT)
                right_sum += point.getIntValue();
            break;
        }
    }

    std::cout << "Diff: " << abs(left_sum - right_sum) << std::endl;
    return abs(left_sum - right_sum);
}