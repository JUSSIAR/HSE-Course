#include "triangle.h"

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3) {
    vertList = {p1, p2, p3};
}

Triangle& Triangle::operator=(const Triangle& other) {
    vertList = other.vertList;
}

Circle Triangle::circumscribedCircle() const {
    double a = distance(vertList[0], vertList[1]);
    double b = distance(vertList[1], vertList[2]);
    double c = distance(vertList[2], vertList[0]);
    double _perim = a + b + c;
    double p = _perim / 2;
    double _area = sqrt(p * (p - a) * (p - b) * (p - c));
    Line side1(vertList[0], vertList[1]);
    Line side2(vertList[0], vertList[2]);
    Point normal1 = side1.getNormal();
    Point normal2 = side2.getNormal();
    Point center1 = (vertList[0] + vertList[1]) * 0.5;
    Point center2 = (vertList[0] + vertList[2]) * 0.5;
    Line pre_bis1(center1, center1 + normal1);
    Line pre_bis2(center2, center2 + normal2);
    Point res_center = getIntersect(pre_bis1, pre_bis2);
    double res_radius = (a * b * c) / (4 * _area);
    return Circle(res_center, res_radius);
}

Circle Triangle::inscribedCircle() const {
    double a = distance(vertList[0], vertList[1]);
    double b = distance(vertList[1], vertList[2]);
    double c = distance(vertList[2], vertList[0]);
    double _perim = a + b + c;
    double p = _perim / 2;
    double _area = sqrt(p * (p - a) * (p - b) * (p - c));
    Point vect_1_1 = vertList[1] - vertList[0];
    Point vect_1_2 = vertList[2] - vertList[0];
    Point vect_2_1 = vertList[0] - vertList[1];
    Point vect_2_2 = vertList[2] - vertList[1];
    double angle1 = fabs(atan2(vect_1_1 ^ vect_1_2, vect_1_1 * vect_1_2));
    double angle2 = fabs(atan2(vect_2_1 ^ vect_2_2, vect_2_1 * vect_2_2));
    Point new_vect1 = rotateVect(vect_1_1, angle1 * sgn(vect_1_1 ^ vect_1_2));
    Point new_vect2 = rotateVect(vect_2_1, angle2 * sgn(vect_2_1 ^ vect_2_2));
    Line bisector1(vertList[0], vertList[0] + new_vect1);
    Line bisector2(vertList[1], vertList[1] + new_vect2);
    Point res_center = getIntersect(bisector1, bisector2);
    double res_radius = (2 * _area) / (_perim);
    return Circle(res_center, res_radius);
}

std::ostream& operator<<(std::ostream& os, const Triangle& t) {
    Triangle copy(t);
    os << '[';
    for (int i = 0; i < 3; i++)
        os << '{' << copy.vertList[i].x << ' ' << copy.vertList[i].y << "} ";
    os << ']' << std::endl;
    return os;
}
