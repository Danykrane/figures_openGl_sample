#include "ui/IconButton.h"

#include "render/ICanvas.h"
#include "scene/Palette.h"
#include "ui/UiDraw.h"

namespace fig {

void IconButton::setBounds(float x, float y, float size) {
    x_ = x;
    y_ = y;
    size_ = size;
}

void IconButton::draw(ICanvas& canvas, const Palette& pal) const {
    if (!visible_) {
        return;
    }
    canvas.fillPolygon(ui::rect(x_, y_, size_, size_), pal.raised);
    canvas.strokePolyline(ui::rect(x_, y_, size_, size_), pal.border, 1.5f, true);

    const float cx = x_ + size_ * 0.5f, cy = y_ + size_ * 0.5f, h = size_ * 0.26f;
    if (icon_ == Icon::Trash) {
        const Color c{0.94f, 0.33f, 0.31f};  // красный
        canvas.strokePolyline({{cx - h, cy - h * 0.7f}, {cx + h, cy - h * 0.7f}}, c, 2.0f, false);
        canvas.strokePolyline({{cx - h * 0.8f, cy - h * 0.5f},
                               {cx + h * 0.8f, cy - h * 0.5f},
                               {cx + h * 0.6f, cy + h},
                               {cx - h * 0.6f, cy + h}},
                              c, 2.0f, true);
    } else {
        canvas.strokePolyline({{cx - h, cy}, {cx + h, cy}}, pal.accent, 3.0f, false);
        canvas.strokePolyline({{cx, cy - h}, {cx, cy + h}}, pal.accent, 3.0f, false);
    }
}

bool IconButton::hitTest(float px, float py) const {
    return visible_ && ui::inRect(px, py, x_, y_, size_, size_);
}

}  // namespace fig
