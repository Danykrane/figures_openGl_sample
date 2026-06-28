#pragma once

#include <cmath>

namespace fig {

// Точка или вектор на плоскости
struct Point2D {
    float x = 0.0f;
    float y = 0.0f;

    Point2D() = default;
    Point2D(float x, float y) : x(x), y(y) {}

    Point2D operator+(Point2D o) const { return {x + o.x, y + o.y}; }
    Point2D operator-(Point2D o) const { return {x - o.x, y - o.y}; }
};

inline float distance(Point2D a, Point2D b) {
    return std::hypot(a.x - b.x, a.y - b.y);
}

}  // namespace fig
