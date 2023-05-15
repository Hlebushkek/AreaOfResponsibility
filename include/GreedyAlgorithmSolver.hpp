#pragma once

#include "Solver.hpp"

class GreedyAlgorithmSolver : public Solver
{
public:
    Line solve(DislocationPoint& pA, DislocationPoint& pB, std::vector<DislocationPoint>& points) override;
};