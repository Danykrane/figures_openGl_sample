#pragma once

#include <string>
#include <vector>

#include "geometry/Color.h"
#include "geometry/Point2D.h"
#include "render/ICanvas.h"

namespace fig {

// Абстрактная фигура: наследники задают имя, площадь, периметр и контур
class Shape {
public:
    explicit Shape(Point2D center) : center_(center) {}
    virtual ~Shape() = default;

    virtual std::string name() const = 0;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::vector<Point2D> outline() const = 0;

    // Обводку и подсветку рисует Window с учётом темы
    void draw(ICanvas& canvas) const { canvas.fillPolygon(outline(), fill_); }

    virtual void moveBy(float dx, float dy) { center_ = center_ + Point2D{dx, dy}; }

    Point2D center() const { return center_; }
    Color fill() const { return fill_; }

    Shape& setFill(Color c) {
        fill_ = c;
        return *this;
    }

protected:
    Point2D center_;
    Color fill_{0.2f, 0.6f, 0.9f};
};

}  // namespace fig
