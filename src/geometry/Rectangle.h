#pragma once

#include "geometry/Shape.h"

namespace fig {

// Прямоугольник со сторонами, параллельными осям
class Rectangle final : public Shape {
public:
    Rectangle(Point2D center, float width, float height)
        : Shape(center), width_(width), height_(height) {}

    // Квадрат это прямоугольник с равными сторонами
    static Rectangle square(Point2D center, float side) { return Rectangle(center, side, side); }

    std::string name() const override { return "Rectangle"; }
    double area() const override;
    double perimeter() const override;
    std::vector<Point2D> outline() const override;

    float width() const { return width_; }
    float height() const { return height_; }

private:
    float width_;
    float height_;
};

}  // namespace fig
