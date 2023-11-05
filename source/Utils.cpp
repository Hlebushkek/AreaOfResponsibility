#include <iostream>
#include "Utils.hpp"
#include "Line.hpp"

bool areAllValuesSimilar(std::vector<int>& values) {
    for (int i = 1; i < values.size(); i++)
        if (values[i] != values[0])
            return false;
    
    return true;
}

void printLines(std::vector<Line>& lines)
{
    for (auto& line : lines)
        std::cout << "StartPoint=(" << line.startPoint.x << "," << line.startPoint.y <<
            "\tEndPoint=(" << line.endPoint.x << "," << line.endPoint.y << std::endl;
}

sf::Vector2f getRandomPoint(const sf::Vector2u& screenSize, const sf::Vector2u& inset)
{
    return sf::Vector2f(rand() % (screenSize.x - inset.x), rand() % (screenSize.y - inset.y));
}