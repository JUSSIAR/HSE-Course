#pragma once
#include "polygon.h"

class Rectangle : public Polygon {
    public:

        Rectangle() = default;
        Rectangle(const Point& p1, const Point& p2, double fake);
        Rectangle(const Rectangle& other) = default;
        Rectangle& operator=(const Rectangle& other);
        ~Rectangle() = default;

        Point center() const;
        std::pair<Line, Line> diagonals() const;
};
