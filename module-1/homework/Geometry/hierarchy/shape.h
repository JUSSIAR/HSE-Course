#pragma once
#include "line.h"

class Shape {
    public:
        Shape() = default;
        virtual ~Shape() = default;

        virtual double perimeter() = 0;
        virtual double area() = 0;
        virtual bool operator==(const Shape& another) = 0;
        virtual bool isCongruentTo(const Shape& another) = 0;
        virtual bool isSimilarTo(const Shape& another) = 0;
        virtual bool containsPoint(const Point& point) = 0;
        virtual void rotate(const Point& center, double angle) = 0;
        virtual void reflex(const Point& center) = 0;
        virtual void reflex(const Line& axis) = 0;
        virtual void scale(const Point& center, double coefficient) = 0;        
};
