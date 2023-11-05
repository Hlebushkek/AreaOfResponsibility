#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

const int BASE_POINT_RADIUS = 8;
const int MAXN = 1000;
const int MAXW = 1000;

const int POPULATION_SIZE = 100;
const float SELECTION_RATE = 0.25;
const float MUTATION_RATE = 2;

struct Line;

bool areAllValuesSimilar(std::vector<int>& values);
void printLines(std::vector<Line>& lines);
sf::Vector2f getRandomPoint(const sf::Vector2u& screenSize, const sf::Vector2u& inset);