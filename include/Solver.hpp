#pragma once

#include <vector>

class DislocationPoint;
struct Line;

class Solver
{
public:
    virtual Line solve(DislocationPoint& pA, DislocationPoint& pB, std::vector<DislocationPoint>& shapes) = 0;
};