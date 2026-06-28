#include "geometry/ShapeFactory.h"

#include "geometry/Circle.h"
#include "geometry/Rectangle.h"
#include "geometry/RegularPolygon.h"
#include "geometry/Triangle.h"

namespace fig {

std::unique_ptr<Shape> makeShape(ShapeKind kind, Point2D center, Color fill) {
    std::unique_ptr<Shape> shape;
    switch (kind) {
        case ShapeKind::Circle:    shape = std::make_unique<Circle>(center, 70.0f); break;
        case ShapeKind::Square:    shape = std::make_unique<Rectangle>(Rectangle::square(center, 130.0f)); break;
        case ShapeKind::Rectangle: shape = std::make_unique<Rectangle>(center, 170.0f, 110.0f); break;
        case ShapeKind::Triangle:  shape = std::make_unique<Triangle>(Triangle::isoscelesByBaseHeight(center, 160.0f, 150.0f)); break;
        case ShapeKind::Pentagon:  shape = std::make_unique<RegularPolygon>(center, 80.0f, 5); break;
        case ShapeKind::Hexagon:   shape = std::make_unique<RegularPolygon>(center, 80.0f, 6); break;
    }
    shape->setFill(fill);
    return shape;
}

}  // namespace fig
