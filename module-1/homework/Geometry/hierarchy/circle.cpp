#include "circle.h"

Circle::Circle(const Point& _cent, double _rad) :
    Ellipse(_cent, _cent, 2 * _rad),
    cent(_cent), rad(_rad) {}

Circle& Circle::operator=(const Circle& other) {
    rad = other.rad;
    cent = other.cent;
    sumDist = rad * 2;
    focus1 = cent;
    focus2 = cent;
    return *this;
}

double Circle::radius() const {
    return rad;
}
