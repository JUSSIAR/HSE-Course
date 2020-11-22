#pragma once
#include "Shape.h"

class Polygon : public Shape{
    public:

        Polygon() = default;
        Polygon(const std::vector<Point>& _vertList);
        Polygon(const Polygon& other) = default;
        Polygon& operator=(const Polygon& other);
        ~Polygon() = default;

        double perimeter() override;
        double area() override;
        bool operator==(const Shape& another) override;
        bool isCongruentTo(const Shape& another) override;
        bool isSimilarTo(const Shape& another) override;
        bool containsPoint(const Point& point) override;
        void rotate(const Point& center, double angle) override;
        void reflex(const Point& center) override;
        void reflex(const Line& axis) override;
        void scale(const Point& center, double coefficient) override;

        size_t verticesCount() const;
        std::vector<Point> getVertices() const;
        bool isConvex() const;
    
    protected:
        std::vector<Point> vertList;

    private:
        bool isSimByK(const Shape& other, size_t start_vert, double k);
        const Polygon* hierarchyAndLen(const Shape& another);
};
