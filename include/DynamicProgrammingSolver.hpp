#pragma once
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include "Solver.hpp"
#include "Line.hpp"
#include "DislocationPoint.hpp"
#include "AORMath.hpp"

class DynamicProgrammingSolver : public Solver
{
    public:
    Line solve(DislocationPoint& pA, DislocationPoint& pB, std::vector<DislocationPoint>& shapes) override
    {
        
        auto dp = DP(pA, pB, shapes, {INT_MAX, {}});
        std::cout<<"Best result: "<<dp.first<<"\n";
        return dp.second;
    }

    std::pair<int, Line> DP(const DislocationPoint& pA, const DislocationPoint& pB, std::vector<DislocationPoint>& points, std::pair<int, Line> currentBest)
    {

        int bestResult = INT_MAX;
        Line bestLine;

        float AB_distance = std::sqrt(std::pow((pB.getPosition().x - pA.getPosition().x), 2) + 
        std::pow((pB.getPosition().y - pA.getPosition().y), 2));

        std::cout<<"Current line length: "<<AB_distance<<std::endl;
        if (AB_distance <= 1)
            return currentBest; 

        sf::Vector2f midAB = sf::Vector2f(
        (pA.getPosition().x + pB.getPosition().x) / 2.f,
        (pA.getPosition().y + pB.getPosition().y) / 2.f);


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

        std::cout<<"Current best line: y = "<<bestLine.k()<<"x + "<<bestLine.b()<<std::endl;

        if (bestResult < currentBest.first)
            currentBest = {bestResult, bestLine};

        auto leftResult = DP(pA, {midAB}, points, currentBest);
        auto rightResult = DP({midAB}, pB, points, currentBest);

        return (leftResult.first < rightResult.first) ?  leftResult : rightResult;
        
    }
};