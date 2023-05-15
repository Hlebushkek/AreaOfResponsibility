#pragma once

#include <SFML/System/Vector2.hpp>
#include <iostream>
#include "Line.hpp"

SIDE determineSide(sf::Vector2f point, Line line)
{
    float line_y = line.k * point.x + line.b;

    if (point.y < line_y)
        return SIDE::RIGHT;
    else if (point.y > line_y)
        return SIDE::LEFT;

    return SIDE::OVERLAY;
}