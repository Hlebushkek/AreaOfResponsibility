#pragma once

#include <vector>
#include <string>

class DislocationPoint;
struct Line;

class Solver
{
public:
    virtual Line solve(DislocationPoint& pA, DislocationPoint& pB, std::vector<DislocationPoint>& shapes) = 0;

    virtual std::string getName() = 0;
};