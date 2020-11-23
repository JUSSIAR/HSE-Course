#include "polygon.h"

Polygon::Polygon(const std::vector<Point>& _vertList) :
    vertList(_vertList) {}

Polygon& Polygon::operator=(const Polygon& other) {
    vertList = other.vertList;
    return *this;
}

double Polygon::perimeter() {
    double res_perim = 0;
    for (size_t i = 0; i < vertList.size(); i++) {
        res_perim += distance(
            vertList[i], 
            vertList[(i + 1) % vertList.size()]
        );
    }
    return res_perim;
}

double Polygon::area() {
    double res_area = 0;
    for (size_t i = 0; i < vertList.size(); i++) {
        res_area += operator^(
            vertList[i], 
            vertList[(i + 1) % vertList.size()]
        );
    }
    return fabs(res_area / 2);
}

bool Polygon::operator==(const Shape& another) {
    const Polygon* other = hierarchyAndLen(another);
    if (other == nullptr)
        return false;
    size_t fake = verticesCount() + 1;
    size_t index = fake;
    for (size_t i = 0; (i < verticesCount()) && (index == fake); i++)
        if (vertList[0] == other->vertList[i])
            index = i;
    if (index == fake)
        return false;
    for (size_t i = 0; i < verticesCount(); i++, index = (index + 1) % (fake - 1))
        if (vertList[i] != other->vertList[index])
            return false;
    return true;
}

bool Polygon::isCongruentTo(const Shape& another) {
    const Polygon* other = hierarchyAndLen(another);
    if (other == nullptr)
        return false;
    for (size_t i = 0; i < verticesCount(); i++)
        if (isSimByK(another, i, 1))
            return true;
    return false;
}

bool Polygon::isSimilarTo(const Shape& another) {
    const Polygon* other = hierarchyAndLen(another);
    if (other == nullptr)
        return false;
    for (size_t i = 0; i < verticesCount(); i++) {
        Point vect_ths = vertList[i] - vertList[(i + 1) % verticesCount()];
        Point vect_oth = other->vertList[i] - other->vertList[(i + 1) % verticesCount()];
        double len_ths = distance(vect_ths, Point(0, 0));
        double len_oth = distance(vect_oth, Point(0, 0));
        if (isSimByK(another, i, len_ths / len_oth))
            return true;
    }
    return false;
}

bool Polygon::containsPoint(const Point& point) {
    double sum = 0;
    for (size_t i = 0; i < vertList.size(); i++) {
        Line side(vertList[i], vertList[(i + 1) % vertList.size()]);
        double min_x = std::min(vertList[i].x, vertList[(i + 1) % vertList.size()].x);
        double min_y = std::min(vertList[i].y, vertList[(i + 1) % vertList.size()].y);
        double max_x = std::max(vertList[i].x, vertList[(i + 1) % vertList.size()].x);
        double max_y = std::max(vertList[i].y, vertList[(i + 1) % vertList.size()].y);
        if ((fabs(side.getDeviation(point)) < EPS) &&
            (min_x + EPS < point.x) && (point.x + EPS < max_x) &&
            (min_y + EPS < point.y) && (point.y + EPS < max_y))
            return true;
        Point vect1 = vertList[i] - point;
        Point vect2 = vertList[(i + 1) % vertList.size()] - point;
        sum += atan2(vect1 ^ vect2, vect1 * vect2);
    }
    return fabs(fabs(sum) - 2 * PI) < EPS;
}

void Polygon::rotate(const Point& center, double angle) {
    angle = PI * angle / 180.0;
    for (size_t i = 0; i < vertList.size(); i++)
        vertList[i] = rotateVect(vertList[i] - center, angle) + center;
}

void Polygon::reflex(const Point& center) {
    for (size_t i = 0; i < vertList.size(); i++)
        vertList[i] = vertList[i] + 2 * (center - vertList[i]);
}

void Polygon::reflex(const Line& axis) {
    Point normal = axis.getNormal();
    normal = (1 / distance(normal, Point(0, 0))) * normal;
    for (size_t i = 0; i < vertList.size(); i++) {
        Point oth = normal + vertList[i];
        Line perp(oth, vertList[i]);
        Point moveVect = getIntersect(perp, axis) - vertList[i];
        vertList[i] = vertList[i] + (moveVect * 2);
    }
}

void Polygon::scale(const Point& center, double coefficient) {
    for (size_t i = 0; i < vertList.size(); i++)
        vertList[i] = coefficient * (vertList[i] - center);
}

size_t Polygon::verticesCount() const {
    return vertList.size();
}

std::vector<Point> Polygon::getVertices() const {
    return vertList;
}

bool Polygon::isConvex() const {
    if (verticesCount() <= 3)
        return true;
    int answer = 0;
    for (size_t i = 0; i < vertList.size(); i++) {
        Point vect1 = vertList[(i + 1) % vertList.size()] - vertList[i];
        Point vect2 = vertList[(i + 2) % vertList.size()] - vertList[(i + 1) % vertList.size()];
        answer += ((fabs(vect1 ^ vect2) < EPS) || (vect1 ^ vect2) > 0) ? 1 : -1;
    }
    return abs(answer) == static_cast<int>(vertList.size());
}

bool Polygon::isSimByK(const Shape& another, size_t start_vert, double k) {
    const Polygon* other = hierarchyAndLen(another);
    if (other == nullptr)
        return false;
    size_t len = verticesCount();
    for (size_t i = 0; i < len; ++i) {
        Point vect1 = vertList[(i + 1) % len] - vertList[i];
        Point vect2 = vertList[(i + 2) % len] - vertList[(i + 1) % len];
        double angle1 = atan2(vect1 ^ vect2, vect1 * vect2);
        Point _vect1 = other->vertList[(i + 1) % len] - other->vertList[i];
        Point _vect2 = other->vertList[(i + 2) % len] - other->vertList[(i + 1) % len];
        double angle2 = atan2(_vect1 ^ _vect2, _vect1 * _vect2);
        if (fabs(distance(Point(0, 0), vect1) - k * distance(Point(0, 0), _vect1)) >= EPS)
            return false;
        if (fabs(distance(Point(0, 0), vect2) - k * distance(Point(0, 0), _vect2)) >= EPS)
            return false;
        if (fabs(angle1 - angle2) >= EPS)
            return false;
    }
    return true;
}

const Polygon* Polygon::hierarchyAndLen(const Shape& another) {
    const Polygon* other = dynamic_cast<const Polygon*>(&another);
    if (other == nullptr)
        return nullptr;
    if (other->verticesCount() != verticesCount())
        return nullptr;
    return other;
}
