#pragma once

#include "scene/Palette.h"

namespace fig {

class ICanvas;

// Кнопка-попап смены темы (правый верхний угол): иконки луна/солнце
class ThemeButton {
public:
    void layout(float windowWidth);
    void draw(ICanvas& canvas, const Palette& pal) const;
    bool onClick(float px, float py);  // true, если клик обработан

    Theme theme() const { return theme_; }

private:
    Theme theme_ = Theme::Dark;
    bool open_ = false;
    float x_ = 0.0f;
    float y_ = 16.0f;
    float size_ = 38.0f;
    float gap_ = 6.0f;
};

}  // namespace fig
