#include "line.h"

Line::Line(const Point& point1, const Point& point2) {
    A = point1.y - point2.y;
    B = point2.x - point1.x;
    C = point1.x * point2.y - point2.x * point1.y;
}

Line& Line::operator=(const Line& other) {
    A = other.A;
    B = other.B;
    C = other.C;
    return *this;
}

bool operator==(const Line& L1, const Line& L2) {
    return (
        (fabs(L1.A - L2.A) < EPS) &&
        (fabs(L1.B - L2.B) < EPS) &&
        (fabs(L1.C - L2.C) < EPS)
    );
}

bool operator!=(const Line& L1, const Line& L2) {
    return !operator==(L1, L2);
}

Point Line::getNormal() const {
    return Point(A, B);
}

double Line::getDeviation(const Point& p) const {
    return A * p.x + B * p.y + C;
}

double Line::getDist(const Point& p) const {
    Point second_p = p + getNormal();
    Line perp(p, second_p);
    return distance(p, getIntersect(*this, perp));
}

Point getIntersect(const Line& l1, const Line& l2) {
    double x = (l2.C * l1.A - l1.C * l2.A) / (l1.B * l2.A - l2.B * l1.A);
    double y = (l2.C * l1.B - l1.C * l2.B) / (l1.A * l2.B - l2.A * l1.B);
    return Point(x, y);
}
