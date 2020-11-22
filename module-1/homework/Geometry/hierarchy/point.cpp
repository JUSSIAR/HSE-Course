#include "point.h"

Point::Point(double _x, double _y) : x(_x), y(_y) {}

Point& Point::operator=(const Point& other) {
    x = other.x;
    y = other.y;
    return *this;
}

bool operator==(const Point& p1, const Point& p2) {
    return (
        (fabs(p1.x - p2.x) < EPS) && 
        (fabs(p1.y - p2.y) < EPS)
    );
}

bool operator!=(const Point& p1, const Point& p2) {
    return !operator==(p1, p2);
}

Point Point::operator-() const {
    return Point(-x, -y);
}

Point operator+(const Point& p1, const Point& p2) {
    return Point(p1.x + p2.x, p1.y + p2.y);
}

Point operator-(const Point& p1, const Point& p2) {
    return Point(p1.x - p2.x, p1.y - p2.y);
}

double operator*(const Point& p1, const Point& p2) {
    return (p1.x * p2.x) + (p1.y * p2.y);
}

double operator^(const Point& p1, const Point& p2) {
    return (p1.x * p2.y) - (p1.y * p2.x);
}

double distance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

Point rotateVect(const Point& p, double angle) {
    double _x = p.x * cos(angle) - p.y * sin(angle);
    double _y = p.x * sin(angle) + p.y * cos(angle);
    return Point(_x, _y);
}

// template <typename T> Point operator*(const Point& p, T k) {
//     return Point(p.x * k, p.y * k);
// }

// template <typename T> Point operator*(T k, const Point& p) {
//     return operator*(p, k);
// }

Point operator*(const Point& p, double k) {
    return Point(p.x * k, p.y * k);
}

Point operator*(double k, const Point& p) {
    return operator*(p, k);
}
