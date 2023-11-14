#pragma once

#include "Solver.hpp"

class GeneticAlgorithmAdvancedSolver : public Solver
{
public:
    GeneticAlgorithmAdvancedSolver(float mr = MUTATION_RATE) : mr(mr) {}

    Line solve(DislocationPoint& pA, DislocationPoint& pB, std::vector<DislocationPoint>& points) override;

    std::vector<Line> generatePopulation(DislocationPoint& pA, DislocationPoint& pB);
    void mutate(Line& line, Line& abLine);
    Line crossover(const Line& parent1, const Line& parent2, Line& abLine);

    std::string getName() override;

private:
    float mr;
};