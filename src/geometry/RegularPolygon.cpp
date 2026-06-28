#define _USE_MATH_DEFINES
#include <cmath>

#include "geometry/RegularPolygon.h"

namespace fig {

RegularPolygon::RegularPolygon(Point2D center, float circumradius, int sides)
    : Shape(center), circumradius_(circumradius), sides_(sides < 3 ? 3 : sides) {}

std::string RegularPolygon::name() const {
    switch (sides_) {
        case 5: return "Pentagon";
        case 6: return "Hexagon";
        case 8: return "Octagon";
        default: return std::to_string(sides_) + "-gon";
    }
}

double RegularPolygon::area() const {
    return 0.5 * sides_ * static_cast<double>(circumradius_) * circumradius_ *
           std::sin(2.0 * M_PI / sides_);
}

double RegularPolygon::perimeter() const {
    return sides_ * 2.0 * circumradius_ * std::sin(M_PI / sides_);
}

std::vector<Point2D> RegularPolygon::outline() const {
    std::vector<Point2D> points;
    points.reserve(static_cast<std::size_t>(sides_));
    for (int i = 0; i < sides_; ++i) {
        const float t = static_cast<float>(2.0 * M_PI * i / sides_ + M_PI / 2.0);
        points.push_back(
            {center_.x + circumradius_ * std::cos(t), center_.y + circumradius_ * std::sin(t)});
    }
    return points;
}

}  // namespace fig
