#pragma once

#include "Solver.hpp"
#include "Line.hpp"

class GreedyAlgorithmSolver : public Solver
{
public:
    Line solve(DislocationPoint &pA, DislocationPoint &pB, std::vector<DislocationPoint> &points) override;

    int calcDiff(std::vector<DislocationPoint> &points, Line line, SIDE onLineAssign = SIDE::OVERLAY);

protected:
    Line bestLine;
    int bestResult;
};