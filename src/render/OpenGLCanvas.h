#pragma once

#include "render/ICanvas.h"

namespace fig {

// Холст поверх классического OpenGL (immediate mode), без загрузчика функций
class OpenGLCanvas final : public ICanvas {
public:
    void fillPolygon(const std::vector<Point2D>& points, const Color& color) override;
    void strokePolyline(const std::vector<Point2D>& points, const Color& color, float width,
                        bool closed) override;
};

}  // namespace fig
