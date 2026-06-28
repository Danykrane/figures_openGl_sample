#pragma once

#include "geometry/Shape.h"

namespace fig {

// Круг, заданный центром и радиусом
class Circle final : public Shape {
public:
    Circle(Point2D center, float radius, int segments = 64)
        : Shape(center), radius_(radius), segments_(segments) {}

    std::string name() const override { return "Circle"; }
    double area() const override;
    double perimeter() const override;
    std::vector<Point2D> outline() const override;

    float radius() const { return radius_; }

private:
    float radius_;
    int segments_;
};

}  // namespace fig
