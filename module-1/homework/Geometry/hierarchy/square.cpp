#include "square.h"

Square::Square(const Point& p1, const Point& p2) :
    Rectangle(p1, p2, 0) {}

Square& Square::operator=(const Square& other) {
    Rectangle::operator=(other);
}

Circle Square::circumscribedCircle() const {
    Point cent = 0.5 * (vertList[0] + vertList[2]);
    double rad = (sqrt(2) / 2) * distance(vertList[0], vertList[1]);
    return Circle(cent, rad);
}

Circle Square::inscribedCircle() const {
    Point cent = 0.5 * (vertList[0] + vertList[2]);
    double rad = 0.5 * distance(vertList[0], vertList[1]);
    return Circle(cent, rad);
}
