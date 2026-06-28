#pragma once

namespace fig {

// Цвет RGBA, компоненты в диапазоне 0..1
struct Color {
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    float a = 1.0f;

    constexpr Color() = default;
    constexpr Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}

    static constexpr Color rgb(int r, int g, int b) {
        return {r / 255.0f, g / 255.0f, b / 255.0f, 1.0f};
    }
};

}  // namespace fig
