#include "ui/ThemeButton.h"

#include <cmath>

#include "render/ICanvas.h"
#include "ui/UiDraw.h"

namespace fig {

namespace {

void drawMoon(ICanvas& canvas, float cx, float cy, float r, const Color& fg, const Color& bg) {
    canvas.fillPolygon(ui::circle(cx, cy, r), fg);
    canvas.fillPolygon(ui::circle(cx + r * 0.45f, cy - r * 0.25f, r * 0.95f), bg);
}

void drawSun(ICanvas& canvas, float cx, float cy, float r, const Color& fg) {
    canvas.fillPolygon(ui::circle(cx, cy, r * 0.6f), fg);
    for (int i = 0; i < 8; ++i) {
        const float a = 6.28318531f * i / 8.0f;
        const float c = std::cos(a), s = std::sin(a);
        canvas.strokePolyline({{cx + c * r * 0.8f, cy + s * r * 0.8f},
                               {cx + c * r * 1.15f, cy + s * r * 1.15f}},
                              fg, 2.0f, false);
    }
}

}  // namespace

void ThemeButton::layout(float windowWidth) {
    x_ = windowWidth - size_ - 16.0f;
}

void ThemeButton::draw(ICanvas& canvas, const Palette& pal) const {
    canvas.fillPolygon(ui::rect(x_, y_, size_, size_), pal.surface);
    canvas.strokePolyline(ui::rect(x_, y_, size_, size_), pal.border, 1.5f, true);

    const float cx = x_ + size_ * 0.5f, cy = y_ + size_ * 0.5f, r = size_ * 0.28f;
    if (theme_ == Theme::Dark) {
        drawMoon(canvas, cx, cy, r, pal.accent, pal.surface);
    } else {
        drawSun(canvas, cx, cy, r, pal.accent);
    }

    if (!open_) {
        return;
    }
    const float py = y_ + size_ + gap_;
    canvas.fillPolygon(ui::rect(x_, py, size_, size_ * 2.0f), pal.raised);
    canvas.strokePolyline(ui::rect(x_, py, size_, size_ * 2.0f), pal.border, 1.5f, true);
    if (theme_ == Theme::Dark) {
        canvas.fillPolygon(ui::rect(x_, py, size_, size_), pal.accent);
    } else {
        canvas.fillPolygon(ui::rect(x_, py + size_, size_, size_), pal.accent);
    }
    drawMoon(canvas, cx, py + size_ * 0.5f, r, pal.text, pal.raised);
    drawSun(canvas, cx, py + size_ * 1.5f, r, pal.text);
}

bool ThemeButton::onClick(float px, float py) {
    if (ui::inRect(px, py, x_, y_, size_, size_)) {
        open_ = !open_;
        return true;
    }
    if (!open_) {
        return false;
    }
    const float menuY = y_ + size_ + gap_;
    if (ui::inRect(px, py, x_, menuY, size_, size_)) {
        theme_ = Theme::Dark;
        open_ = false;
        return true;
    }
    if (ui::inRect(px, py, x_, menuY + size_, size_, size_)) {
        theme_ = Theme::Light;
        open_ = false;
        return true;
    }
    open_ = false;
    return true;
}

}  // namespace fig
