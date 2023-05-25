#pragma once
#include "Solver.hpp"

class DynamicProgrammingSolver : public Solver
{
    public:
    Line solve(DislocationPoint& pA, DislocationPoint& pB, std::vector<DislocationPoint>& shapes) override;
    std::pair<int, Line> DP(const DislocationPoint& pA, const DislocationPoint& pB, std::vector<DislocationPoint>& points, std::pair<int, Line> currentBest);

    std::string getName() override;
};