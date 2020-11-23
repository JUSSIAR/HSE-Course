#pragma once
#include "ellipse.h"

class Circle : public Ellipse {
    public:

        Circle() = default;
        Circle(const Point& _cent, double _rad);
        Circle(const Circle& other) = default;
        Circle& operator=(const Circle& other);
        ~Circle() = default;

        double radius() const;

    private:
        Point cent;
        double rad;
};
