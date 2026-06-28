#pragma once

#include <iosfwd>
#include <memory>
#include <utility>
#include <vector>

#include "geometry/Shape.h"

namespace fig {

class ICanvas;

// Полиморфный контейнер фигур: хранит их через указатель на базовый класс
class Scene {
public:
    template <typename T, typename... Args>
    T& add(Args&&... args) {
        auto shape = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *shape;
        shapes_.push_back(std::move(shape));
        return ref;
    }

    const std::vector<std::unique_ptr<Shape>>& shapes() const { return shapes_; }
    std::size_t size() const { return shapes_.size(); }

    Shape& at(std::size_t i) { return *shapes_.at(i); }
    const Shape& at(std::size_t i) const { return *shapes_.at(i); }
    void addShape(std::unique_ptr<Shape> shape) { shapes_.push_back(std::move(shape)); }
    void removeAt(std::size_t i) {
        if (i < shapes_.size()) {
            shapes_.erase(shapes_.begin() + static_cast<std::ptrdiff_t>(i));
        }
    }

    void drawAll(ICanvas& canvas) const;
    double totalArea() const;
    void printReport(std::ostream& os) const;

private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};

}  // namespace fig
