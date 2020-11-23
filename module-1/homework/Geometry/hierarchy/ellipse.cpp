#include "ellipse.h"

Ellipse::Ellipse(const Point& f1, const Point& f2, double _sumDist) :
    focus1(f1),
    focus2(f2),
    sumDist(_sumDist) {}

Ellipse& Ellipse::operator=(const Ellipse& other) {
    focus1 = other.focus1;
    focus2 = other.focus2;
    sumDist = other.sumDist;
}

double Ellipse::perimeter() {
    double a = sumDist / 2;
    double b = getB();
    return 4 * (PI * a * b + (a - b) * (a - b)) / (a + b);
}

double Ellipse::area() {
    double a = sumDist / 2;
    double b = getB();
    return PI * a * b;
}

bool Ellipse::operator==(const Shape& another) {
    const Ellipse* other = dynamic_cast<const Ellipse*>(&another);
    if (other == nullptr)
        return false;
    if (fabs(sumDist - other->sumDist) >= EPS)
        return false;
    return (
        ((focus1 == other->focus1) && (focus2 == other->focus2)) ||
        ((focus2 == other->focus1) && (focus1 == other->focus2))
    );
}

bool Ellipse::isCongruentTo(const Shape& another) {
    const Ellipse* other = dynamic_cast<const Ellipse*>(&another);
    if (other == nullptr)
        return false; 
    return (
        (fabs(sumDist - other->sumDist) < EPS) &&
        (fabs(distance(focus1, focus2) - distance(other->focus1, other->focus2)) < EPS)
    );
}

bool Ellipse::isSimilarTo(const Shape& another) {
    const Ellipse* other = dynamic_cast<const Ellipse*>(&another);
    if (other == nullptr)
        return false;
    return (fabs(
        distance(focus1, focus2) * other->sumDist - 
        distance(other->focus1, other->focus2) * sumDist) < EPS
    );
}

bool Ellipse::containsPoint(const Point& point) {
    double dist1 = distance(focus1, point);
    double dist2 = distance(focus2, point);
    return (dist1 + dist2 + EPS < sumDist);
}

void Ellipse::rotate(const Point& center, double angle) {
    angle = PI * angle / 180.0;
    focus1 = rotateVect(focus1 - center, angle) + center;
    focus2 = rotateVect(focus2 - center, angle) + center;
}

void Ellipse::reflex(const Point& center) {
    focus1 = focus1 + 2 * (center - focus1);
    focus2 = focus2 + 2 * (center - focus2);
}

void Ellipse::reflex(const Line& axis) {
    Point normal = axis.getNormal();
    normal = (1 / distance(normal, Point(0, 0))) * normal;
    double dev1 = axis.getDeviation(focus1);
    Point moveVect1 = (2 * dev1) * normal;
    focus1 = focus1 - moveVect1;
    double dev2 = axis.getDeviation(focus2);
    Point moveVect2 = (2 * dev2) * normal;
    focus2 = focus2 - moveVect2;
}

void Ellipse::scale(const Point& center, double coefficient) {
    focus1 = coefficient * (focus1 - center);
    focus2 = coefficient * (focus2 - center);
}

std::pair<Point, Point> Ellipse::focuses() const {
    return std::make_pair(focus1, focus2);
}

std::pair<Line, Line> Ellipse::directrices() const {
    Line dir1(focus1, focus2);
    Point normal = dir1.getNormal();
    Point cent = center();
    Line dir2(cent, cent + normal);
    return std::make_pair(dir1, dir2);
}

double Ellipse::eccentricity() const {
    double dir = distance(focus1, focus2);
    return dir / sumDist;
}

Point Ellipse::center() const {
    return 0.5 * (focus1 + focus2);
}

double Ellipse::getB() const {
    double kat = distance(focus1, focus2) / 2;
    double gip = sumDist / 2;
    return sqrt(gip * gip - kat * kat);    
}
