#pragma once

#include "geometry/Shape.h"

namespace fig {

// Треугольник по трём вершинам; центр это центроид
class Triangle final : public Shape {
public:
    Triangle(Point2D a, Point2D b, Point2D c);

    // Равнобедренный треугольник по центру, ширине основания и высоте
    static Triangle isoscelesByBaseHeight(Point2D center, float base, float height);

    std::string name() const override { return "Triangle"; }
    double area() const override;
    double perimeter() const override;
    std::vector<Point2D> outline() const override;
    void moveBy(float dx, float dy) override;

private:
    Point2D a_, b_, c_;
};

}  // namespace fig
