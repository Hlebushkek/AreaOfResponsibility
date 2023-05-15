#include "AORMath.hpp"
#include "Line.hpp"
#include "DislocationPoint.hpp"

SIDE AORMath::determineSide(sf::Vector2f point, Line line)
{
    float line_y = line.k() * point.x + line.b();

    if (point.y < line_y)
        return SIDE::RIGHT;
    else if (point.y > line_y)
        return SIDE::LEFT;

    return SIDE::OVERLAY;
}

int AORMath::calcDiff(const std::vector<DislocationPoint> &points, const Line &line, SIDE onLineAssign)
{
    int leftSum = 0;
    int rightSum = 0;

    for (auto point : points)
    {
        SIDE side = determineSide(point.getPosition(), line);

        switch (side)
        {
        case LEFT:
            leftSum += point.getIntValue();
            break;
        case RIGHT:
            rightSum += point.getIntValue();
            break;
        case OVERLAY:
            if (onLineAssign == SIDE::LEFT)
                leftSum += point.getIntValue();
            else if (onLineAssign == SIDE::RIGHT)
                rightSum += point.getIntValue();
            break;
        }
    }

    return abs(leftSum - rightSum);
}