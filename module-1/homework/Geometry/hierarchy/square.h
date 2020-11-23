#pragma once
#include "rectangle.h"
#include "circle.h"

class Square : public Rectangle {
    public:
        Square() = default;
        Square(const Point& p1, const Point& p2);
        Square(const Square& other) = default;
        Square& operator=(const Square& other);
        ~Square() = default;

        Circle circumscribedCircle() const;
        Circle inscribedCircle() const;
};
