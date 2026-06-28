#pragma once

#include <vector>

#include "geometry/Color.h"
#include "geometry/Point2D.h"

namespace fig {

// Абстракция рисования (паттерн Мост): фигуры и интерфейс не зависят от OpenGL
class ICanvas {
public:
    virtual ~ICanvas() = default;

    virtual void fillPolygon(const std::vector<Point2D>& points, const Color& color) = 0;
    virtual void strokePolyline(const std::vector<Point2D>& points, const Color& color,
                                float width, bool closed) = 0;
};

}  // namespace fig
