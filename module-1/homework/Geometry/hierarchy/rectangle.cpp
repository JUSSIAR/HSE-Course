#include "rectangle.h"

Rectangle::Rectangle(const Point& p1, const Point& p2, double fake) {
    double min_x = std::min(p1.x, p2.x);
    double min_y = std::min(p1.y, p2.y);
    double max_x = std::max(p1.x, p2.x);
    double max_y = std::max(p1.y, p2.y);
    vertList.push_back(Point(min_x, min_y));
    vertList.push_back(Point(max_x, min_y));
    vertList.push_back(Point(max_x, max_y));
    vertList.push_back(Point(min_x, max_y));
}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    vertList = other.vertList;
    return *this;
}

Point Rectangle::center() const {
    return 0.5 * (vertList[0] + vertList[2]);
}

std::pair<Line, Line> Rectangle::diagonals() const {
    return std::make_pair(
        Line(vertList[0], vertList[2]),
        Line(vertList[1], vertList[3])
    );
}
