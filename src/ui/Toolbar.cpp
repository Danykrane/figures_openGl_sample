#include "ui/Toolbar.h"

#include <cmath>
#include <vector>

#include "render/ICanvas.h"
#include "scene/Palette.h"
#include "ui/UiDraw.h"

namespace fig {

namespace {

constexpr float kLeft = 16.0f;
constexpr float kTop = 12.0f;
constexpr float kBar = 40.0f;
constexpr float kCell = 46.0f;
constexpr float kPad = 8.0f;
constexpr float kAddH = 30.0f;
constexpr float kInvW = kPad + kShapeKindCount * (kCell + kPad);
constexpr float kInvTop = kTop + kBar + 6.0f;
constexpr float kInvH = kPad + kCell + kPad + kAddH + kPad;

float cellX(int i) { return kLeft + kPad + i * (kCell + kPad); }
float cellY() { return kInvTop + kPad; }
float addY() { return kInvTop + kPad + kCell + kPad; }

// Контур-иконка фигуры в точке (cx, cy) радиуса r, экран Y вниз
std::vector<Point2D> iconPoly(ShapeKind k, float cx, float cy, float r) {
    auto regular = [&](int n) {
        std::vector<Point2D> p;
        for (int i = 0; i < n; ++i) {
            const float a = -1.5707963f + 6.28318531f * i / n;
            p.push_back({cx + r * std::cos(a), cy + r * std::sin(a)});
        }
        return p;
    };
    switch (k) {
        case ShapeKind::Circle: return ui::circle(cx, cy, r, 24);
        case ShapeKind::Square: return ui::rect(cx - r * 0.85f, cy - r * 0.85f, r * 1.7f, r * 1.7f);
        case ShapeKind::Rectangle: return ui::rect(cx - r * 1.25f, cy - r * 0.8f, r * 2.5f, r * 1.6f);
        case ShapeKind::Triangle:
            return {{cx, cy - r}, {cx + r * 0.92f, cy + r * 0.62f}, {cx - r * 0.92f, cy + r * 0.62f}};
        case ShapeKind::Pentagon: return regular(5);
        case ShapeKind::Hexagon: return regular(6);
    }
    return {};
}

void drawIcon(ICanvas& canvas, ShapeKind k, float cx, float cy, float r) {
    canvas.fillPolygon(iconPoly(k, cx, cy, r), kShapeColors[static_cast<std::size_t>(k)]);
}

}  // namespace

void Toolbar::draw(ICanvas& canvas, const Palette& pal) const {
    canvas.fillPolygon(ui::rect(kLeft, kTop, kBar, kBar), open_ ? pal.raised : pal.surface);
    canvas.strokePolyline(ui::rect(kLeft, kTop, kBar, kBar), open_ ? pal.accent : pal.border, 1.5f, true);
    drawIcon(canvas, selected_, kLeft + kBar * 0.5f, kTop + kBar * 0.5f, 12.0f);
    // уголок-индикатор
    const float ax = kLeft + kBar - 9.0f, ay = kTop + kBar - 9.0f;
    canvas.fillPolygon({{ax - 4, ay - 2}, {ax + 4, ay - 2}, {ax, ay + 3}}, pal.accent);

    if (!open_) {
        return;
    }
    canvas.fillPolygon(ui::rect(kLeft, kInvTop, kInvW, kInvH), pal.raised);
    canvas.strokePolyline(ui::rect(kLeft, kInvTop, kInvW, kInvH), pal.border, 1.5f, true);
    for (int i = 0; i < kShapeKindCount; ++i) {
        const bool sel = static_cast<ShapeKind>(i) == selected_;
        canvas.fillPolygon(ui::rect(cellX(i), cellY(), kCell, kCell), sel ? pal.surface : pal.bg);
        canvas.strokePolyline(ui::rect(cellX(i), cellY(), kCell, kCell), sel ? pal.accent : pal.border,
                              sel ? 2.0f : 1.0f, true);
        drawIcon(canvas, static_cast<ShapeKind>(i), cellX(i) + kCell * 0.5f, cellY() + kCell * 0.5f, 15.0f);
    }
    canvas.fillPolygon(ui::rect(kLeft + kPad, addY(), kInvW - 2 * kPad, kAddH), pal.accent);
    const float mx = kLeft + kInvW * 0.5f, my = addY() + kAddH * 0.5f;
    const Color white{1.0f, 1.0f, 1.0f};
    canvas.strokePolyline({{mx - 9, my}, {mx + 9, my}}, white, 3.0f, false);
    canvas.strokePolyline({{mx, my - 9}, {mx, my + 9}}, white, 3.0f, false);
}

Toolbar::Action Toolbar::onClick(float px, float py) {
    if (ui::inRect(px, py, kLeft, kTop, kBar, kBar)) {
        open_ = !open_;
        return Action::Consumed;
    }
    if (!open_) {
        return Action::None;
    }
    for (int i = 0; i < kShapeKindCount; ++i) {
        if (ui::inRect(px, py, cellX(i), cellY(), kCell, kCell)) {
            selected_ = static_cast<ShapeKind>(i);
            return Action::Consumed;
        }
    }
    if (ui::inRect(px, py, kLeft + kPad, addY(), kInvW - 2 * kPad, kAddH)) {
        return Action::AddShape;
    }
    if (ui::inRect(px, py, kLeft, kInvTop, kInvW, kInvH)) {
        return Action::Consumed;
    }
    open_ = false;
    return Action::None;
}

}  // namespace fig
