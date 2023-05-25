#include "Line.hpp"

sf::Vector2f Line::randomlyMovePointAlongLine(sf::Vector2f point, float multiplier, float bound1, float bound2)
{
    float xMin = bound1 >= bound2 ? bound2 : bound1;
    float xMax = bound1 < bound2 ? bound2 : bound1;

    float x = point.x + ((static_cast<float>(rand()) / RAND_MAX) - 0.5) * multiplier;

            if (x < xMin) x = xMin;
    else if (x > xMax) x = xMax;

    return sf::Vector2f(x, k() * x + b());
}

sf::Vector2f Line::getPointOnLineSegment(float bound1, float bound2)
{
    float xMin = bound1 >= bound2 ? bound2 : bound1;
    float xMax = bound1 < bound2 ? bound2 : bound1;

    float x = (static_cast<float>(rand()) / RAND_MAX) * (xMax - xMin) + xMin;
    return sf::Vector2f(x, k() * x + b());
}

std::ostream &operator<<(std::ostream &os, const Line &obj)
{
    os << "y = " << obj.k() << "x + " << obj.b();
    return os;
}
