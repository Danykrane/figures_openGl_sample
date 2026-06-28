#define _USE_MATH_DEFINES
#include <cmath>

#include <gtest/gtest.h>

#include "geometry/Circle.h"
#include "geometry/Rectangle.h"
#include "geometry/RegularPolygon.h"
#include "geometry/Triangle.h"
#include "scene/Scene.h"

using namespace fig;

TEST(Circle, AreaAndPerimeter) {
    Circle c({0, 0}, 2.0f);
    EXPECT_NEAR(c.area(), M_PI * 4.0, 1e-4);
    EXPECT_NEAR(c.perimeter(), 4.0 * M_PI, 1e-4);
    EXPECT_EQ(c.name(), "Circle");
}

TEST(Rectangle, AreaAndPerimeter) {
    Rectangle r({0, 0}, 4.0f, 3.0f);
    EXPECT_DOUBLE_EQ(r.area(), 12.0);
    EXPECT_DOUBLE_EQ(r.perimeter(), 14.0);
    EXPECT_EQ(r.outline().size(), 4u);
}

TEST(Rectangle, SquareFactory) {
    Rectangle s = Rectangle::square({0, 0}, 5.0f);
    EXPECT_DOUBLE_EQ(s.area(), 25.0);
    EXPECT_DOUBLE_EQ(s.perimeter(), 20.0);
}

TEST(Triangle, RightTriangle) {
    Triangle t({0, 0}, {4, 0}, {0, 3});
    EXPECT_DOUBLE_EQ(t.area(), 6.0);
    EXPECT_DOUBLE_EQ(t.perimeter(), 12.0);
}

TEST(RegularPolygon, HexagonAndName) {
    RegularPolygon hex({0, 0}, 1.0f, 6);
    EXPECT_NEAR(hex.perimeter(), 6.0, 1e-4);
    EXPECT_EQ(hex.name(), "Hexagon");
    EXPECT_EQ(RegularPolygon({0, 0}, 1.0f, 5).name(), "Pentagon");
}

TEST(Scene, PolymorphicTotalArea) {
    Scene scene;
    scene.add<Rectangle>(Rectangle::square(Point2D{0, 0}, 2.0f));
    scene.add<Rectangle>(Point2D{0, 0}, 2.0f, 3.0f);
    EXPECT_EQ(scene.size(), 2u);
    EXPECT_DOUBLE_EQ(scene.totalArea(), 10.0);
}
