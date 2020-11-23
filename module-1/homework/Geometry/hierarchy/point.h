#pragma once
#include "constantList.h"

class Point {

    friend class Line;
    friend class Shape;
    friend class Polygon;
    friend class Rectangle;
    friend class Ellipse;
    friend class Circle;
    friend class Square;
    friend class Triangle;

    public:
        double x;
        double y;

        Point() = default;
        Point(double _x, double _y);
        Point(const Point& other) = default;
        Point& operator=(const Point& other);
        ~Point() = default;

        Point operator-() const;

        friend bool operator==(const Point& p1, const Point& p2);
        friend bool operator!=(const Point& p1, const Point& p2);

        friend Point operator+(const Point& p1, const Point& p2);
        friend Point operator-(const Point& p1, const Point& p2);
        
        friend double operator*(const Point& p1, const Point& p2);
        friend double operator^(const Point& p1, const Point& p2);

        friend double distance(const Point& p1, const Point& p2);
        friend Point rotateVect(const Point& p, double angle);

        // template <typename T> friend Point operator*(const Point& p, T k);
        // template <typename T> friend Point operator*(T k, const Point& p);

        friend Point operator*(const Point& p, double k);
        friend Point operator*(double k, const Point& p);
};
