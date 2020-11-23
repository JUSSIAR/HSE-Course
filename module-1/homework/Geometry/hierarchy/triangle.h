#pragma once
#include "polygon.h"
#include "circle.h"

class Triangle : public Polygon {
    public:
        Triangle() = default;
        Triangle(const Point& p1, const Point& p2, const Point& p3);
        Triangle(const Triangle& other) = default;
        Triangle& operator=(const Triangle& other);
        ~Triangle() = default;

        Circle circumscribedCircle() const;
        Circle inscribedCircle() const;
        
};
