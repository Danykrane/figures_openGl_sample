#define _USE_MATH_DEFINES
#include <cmath>

#include "geometry/Circle.h"

namespace fig {

double Circle::area() const {
    return M_PI * radius_ * radius_;
}

double Circle::perimeter() const {
    return 2.0 * M_PI * radius_;
}

std::vector<Point2D> Circle::outline() const {
    std::vector<Point2D> points;
    points.reserve(static_cast<std::size_t>(segments_));
    for (int i = 0; i < segments_; ++i) {
        const float t = static_cast<float>(2.0 * M_PI * i / segments_);
        points.push_back({center_.x + radius_ * std::cos(t), center_.y + radius_ * std::sin(t)});
    }
    return points;
}

}  // namespace fig
