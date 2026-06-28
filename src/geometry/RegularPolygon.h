#pragma once

#include "geometry/Shape.h"

namespace fig {

// Правильный многоугольник (пятиугольник, шестиугольник)
class RegularPolygon final : public Shape {
public:
    RegularPolygon(Point2D center, float circumradius, int sides);

    std::string name() const override;
    double area() const override;
    double perimeter() const override;
    std::vector<Point2D> outline() const override;

    int sides() const { return sides_; }

private:
    float circumradius_;
    int sides_;
};

}  // namespace fig
