#pragma once

#include <array>

#include "geometry/Color.h"

namespace fig {

enum class Theme { Dark, Light };

// Цвета интерфейса для одной темы
struct Palette {
    Color bg;
    Color surface;
    Color raised;
    Color border;
    Color accent;
    Color accentHover;
    Color text;
};

inline constexpr Palette kDark{
    Color::rgb(0x10, 0x12, 0x16), Color::rgb(0x1B, 0x22, 0x30), Color::rgb(0x2A, 0x31, 0x42),
    Color::rgb(0x3D, 0x46, 0x58), Color::rgb(0x26, 0xC6, 0xDA), Color::rgb(0x4D, 0xD0, 0xE1),
    Color::rgb(0xE6, 0xE1, 0xCF),
};

inline constexpr Palette kLight{
    Color::rgb(0xE8, 0xED, 0xF3), Color::rgb(0xF4, 0xF6, 0xFA), Color::rgb(0xD3, 0xD8, 0xE0),
    Color::rgb(0x8C, 0x97, 0xA8), Color::rgb(0x0E, 0x7F, 0x92), Color::rgb(0x12, 0x9A, 0xB0),
    Color::rgb(0x1A, 0x23, 0x33),
};

inline constexpr const Palette& paletteFor(Theme theme) {
    return theme == Theme::Dark ? kDark : kLight;
}

// Цвета фигур не зависят от темы
inline constexpr std::array<Color, 6> kShapeColors{
    Color::rgb(0x26, 0xC6, 0xDA), Color::rgb(0xFF, 0xB3, 0x00), Color::rgb(0x66, 0xBB, 0x6A),
    Color::rgb(0xEF, 0x53, 0x50), Color::rgb(0xAB, 0x7D, 0xF0), Color::rgb(0x29, 0xB6, 0xF6),
};

}  // namespace fig
