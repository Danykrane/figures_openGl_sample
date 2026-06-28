#pragma once

#include <cmath>
#include <vector>

#include "geometry/Point2D.h"

namespace fig::ui {

inline std::vector<Point2D> rect(float x, float y, float w, float h) {
    return {{x, y}, {x + w, y}, {x + w, y + h}, {x, y + h}};
}

inline std::vector<Point2D> circle(float cx, float cy, float r, int segments = 40) {
    std::vector<Point2D> pts;
    pts.reserve(static_cast<std::size_t>(segments));
    for (int i = 0; i < segments; ++i) {
        const float a = 6.28318531f * i / segments;
        pts.push_back({cx + r * std::cos(a), cy + r * std::sin(a)});
    }
    return pts;
}

inline bool inRect(float px, float py, float x, float y, float w, float h) {
    return px >= x && px <= x + w && py >= y && py <= y + h;
}

}  // namespace fig::ui
