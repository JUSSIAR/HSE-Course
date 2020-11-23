#pragma once
#include "shape.h"

class Ellipse : public Shape {
    public:

        Ellipse() = default;
        Ellipse(const Point& f1, const Point& f2, double _sumDist);
        Ellipse(const Ellipse& other) = default;
        Ellipse& operator=(const Ellipse& other);
        ~Ellipse() = default;

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

        std::pair<Point, Point> focuses() const;
        std::pair<Line, Line> directrices() const;
        double eccentricity() const;
        Point center() const;
    
    protected:
        Point focus1;
        Point focus2;
        double sumDist;
        
    private:
        double getB() const;
};
