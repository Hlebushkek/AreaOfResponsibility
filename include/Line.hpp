#pragma once
#include <stdlib.h>
#include <limits.h>
#include <SFML/System/Vector2.hpp>

struct Line
{
    Line(sf::Vector2f a, sf::Vector2f b) : startPoint(a), endPoint(b) {}
    Line() : Line(sf::Vector2f(0, 0), sf::Vector2f(0, 1)) {}

    sf::Vector2f startPoint;
    sf::Vector2f endPoint;

    float k() const { return (endPoint.y - startPoint.y) / (endPoint.x - startPoint.x); } 
    float b() const { return startPoint.y - k() * startPoint.x; }

    sf::Vector2f randomlyMovePointAlongLine(sf::Vector2f point, float multiplier = 1.f, float bound1 = INT_MIN, float bound2 = INT_MAX)
    {
        float xMin = bound1 >= bound2 ? bound2 : bound1;
        float xMax = bound1 < bound2 ? bound2 : bound1;

        float x = point.x + ((static_cast<float>(rand()) / RAND_MAX) - 0.5) * multiplier;

             if (x < xMin) x = xMin;
        else if (x > xMax) x = xMax;

        return sf::Vector2f(x, k() * x + b());
    }

    sf::Vector2f getPointOnLineSegment(float bound1, float bound2)
    {
        float xMin = bound1 >= bound2 ? bound2 : bound1;
        float xMax = bound1 < bound2 ? bound2 : bound1;

        float x = (static_cast<float>(rand()) / RAND_MAX) * (xMax - xMin) + xMin;
        return sf::Vector2f(x, k() * x + b());
    }

    bool operator==(const Line& other) const {
        return k() == other.k() && b() == other.b();
    }
};