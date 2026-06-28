#include "render/OpenGLCanvas.h"

// Заголовок OpenGL зависит от платформы; для immediate mode загрузчик не нужен
#if defined(__APPLE__)
#define GL_SILENCE_DEPRECATION  // на macOS OpenGL помечен устаревшим
#include <OpenGL/gl.h>
#elif defined(_WIN32)
#include <windows.h>  // на Windows GL/gl.h требует windows.h до себя
#include <GL/gl.h>
#else
#include <GL/gl.h>
#endif

namespace fig {

void OpenGLCanvas::fillPolygon(const std::vector<Point2D>& points, const Color& color) {
    if (points.size() < 3) {
        return;
    }
    glColor4f(color.r, color.g, color.b, color.a);
    glBegin(GL_POLYGON);
    for (const Point2D& p : points) {
        glVertex2f(p.x, p.y);
    }
    glEnd();
}

void OpenGLCanvas::strokePolyline(const std::vector<Point2D>& points, const Color& color,
                                  float width, bool closed) {
    if (points.size() < 2) {
        return;
    }
    glLineWidth(width);
    glColor4f(color.r, color.g, color.b, color.a);
    glBegin(closed ? GL_LINE_LOOP : GL_LINE_STRIP);
    for (const Point2D& p : points) {
        glVertex2f(p.x, p.y);
    }
    glEnd();
}

}  // namespace fig
