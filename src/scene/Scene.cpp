#include "scene/Scene.h"

#include <iomanip>
#include <ostream>

#include "render/ICanvas.h"

namespace fig {

void Scene::drawAll(ICanvas& canvas) const {
    for (const auto& shape : shapes_) {
        shape->draw(canvas);
    }
}

double Scene::totalArea() const {
    double sum = 0.0;
    for (const auto& shape : shapes_) {
        sum += shape->area();
    }
    return sum;
}

void Scene::printReport(std::ostream& os) const {
    os << std::left << std::setw(12) << "Shape" << std::right << std::setw(14) << "Area"
       << std::setw(14) << "Perimeter" << '\n';
    os << std::string(40, '-') << '\n';
    os << std::fixed << std::setprecision(2);
    for (const auto& shape : shapes_) {
        os << std::left << std::setw(12) << shape->name() << std::right << std::setw(14)
           << shape->area() << std::setw(14) << shape->perimeter() << '\n';
    }
}

}  // namespace fig
