#include "geometry/Rectangle.h"

namespace fig {

double Rectangle::area() const {
    return static_cast<double>(width_) * height_;
}

double Rectangle::perimeter() const {
    return 2.0 * (static_cast<double>(width_) + height_);
}

std::vector<Point2D> Rectangle::outline() const {
    const float hw = width_ * 0.5f;
    const float hh = height_ * 0.5f;
    return {{center_.x - hw, center_.y - hh},
            {center_.x + hw, center_.y - hh},
            {center_.x + hw, center_.y + hh},
            {center_.x - hw, center_.y + hh}};
}

}  // namespace fig
