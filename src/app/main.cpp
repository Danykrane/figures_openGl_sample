#include <cstring>
#include <iostream>

#include "geometry/Circle.h"
#include "geometry/Rectangle.h"
#include "geometry/RegularPolygon.h"
#include "geometry/Triangle.h"
#include "render/Window.h"
#include "scene/Palette.h"
#include "scene/Scene.h"

namespace {

fig::Scene buildScene() {
    using namespace fig;
    Scene scene;
    scene.add<Circle>(Point2D{150, 430}, 80).setFill(kShapeColors[0]);
    scene.add<Rectangle>(Rectangle::square(Point2D{400, 430}, 150)).setFill(kShapeColors[1]);
    scene.add<Rectangle>(Point2D{650, 430}, 190, 120).setFill(kShapeColors[2]);
    scene.add<Triangle>(Triangle::isoscelesByBaseHeight(Point2D{170, 160}, 190, 170))
        .setFill(kShapeColors[3]);
    scene.add<RegularPolygon>(Point2D{430, 160}, 95, 5).setFill(kShapeColors[4]);
    scene.add<RegularPolygon>(Point2D{670, 160}, 90, 6).setFill(kShapeColors[5]);
    return scene;
}

}  // namespace

int main(int argc, char** argv) {
    // Единственный флаг: --headless печатает отчёт и выходит без окна
    const bool headless = argc > 1 && std::strcmp(argv[1], "--headless") == 0;

    fig::Scene scene = buildScene();
    scene.printReport(std::cout);
    if (headless) {
        return 0;
    }

    try {
        fig::Window window(960, 720, "openGl_figures");
        window.setWorldSize(800, 600);
        while (window.isOpen()) {
            window.pollEvents();
            window.render(scene);
        }
    } catch (const fig::WindowError& e) {
        std::cerr << "Cannot open window: " << e.what() << "\nUse --headless for text output\n";
        return 0;
    }
    return 0;
}
