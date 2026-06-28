#pragma once

#include <memory>

#include "geometry/Color.h"
#include "geometry/Point2D.h"
#include "geometry/Shape.h"

namespace fig {

enum class ShapeKind { Circle, Square, Rectangle, Triangle, Pentagon, Hexagon };
inline constexpr int kShapeKindCount = 6;

// Фабрика фигур: создаёт фигуру заданного вида в точке center
std::unique_ptr<Shape> makeShape(ShapeKind kind, Point2D center, Color fill);

}  // namespace fig
