#pragma once
#include "point.h"

class Line {

    friend class Point;
    friend class Shape;
    friend class Polygon;
    friend class Rectangle;
    friend class Ellipse;
    friend class Circle;
    friend class Square;
    friend class Triangle;

    public:
        Line() = default;
        Line(const Point& _point1, const Point& _point2);
        Line(const Line& other) = default;
        Line& operator=(const Line& other);
        ~Line() = default;

        friend bool operator==(const Line& L1, const Line& L2);
        friend bool operator!=(const Line& L1, const Line& L2);
        
        Point getNormal() const;
        double getDeviation(const Point& p) const;
        double getDist(const Point& p) const;
        
    private:

        double A;
        double B;
        double C;

        friend Point getIntersect(const Line& l1, const Line& l2);
};
