#pragma once

enum Colors { RED, GREEN, BLUE };

struct Point
{
    int x, y;
    int weight;
    int type;

    Point(int x, int y, int type): x(x), y(y), type(type), weight(1) {}
};