#pragma once

#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>

struct Line;
class DislocationPoint;

enum SIDE { LEFT, RIGHT, OVERLAY };

class AORMath
{
public:
    static SIDE determineSide(sf::Vector2f point, Line line);
    static int calcDiff(const std::vector<DislocationPoint>& points, const Line& line, SIDE onLineAssign = SIDE::OVERLAY);
};