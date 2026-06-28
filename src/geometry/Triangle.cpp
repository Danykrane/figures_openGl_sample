#include "geometry/Triangle.h"

#include <cmath>

namespace fig {

Triangle::Triangle(Point2D a, Point2D b, Point2D c)
    : Shape({(a.x + b.x + c.x) / 3.0f, (a.y + b.y + c.y) / 3.0f}), a_(a), b_(b), c_(c) {}

double Triangle::area() const {
    return std::fabs((b_.x - a_.x) * (c_.y - a_.y) - (c_.x - a_.x) * (b_.y - a_.y)) * 0.5;
}

double Triangle::perimeter() const {
    return distance(a_, b_) + distance(b_, c_) + distance(c_, a_);
}

std::vector<Point2D> Triangle::outline() const {
    return {a_, b_, c_};
}

void Triangle::moveBy(float dx, float dy) {
    const Point2D d{dx, dy};
    a_ = a_ + d;
    b_ = b_ + d;
    c_ = c_ + d;
    center_ = center_ + d;
}

Triangle Triangle::isoscelesByBaseHeight(Point2D center, float base, float height) {
    const float hb = base * 0.5f;
    const float hh = height * 0.5f;
    return Triangle({center.x - hb, center.y - hh}, {center.x + hb, center.y - hh},
                    {center.x, center.y + hh});
}

}  // namespace fig
