#pragma once

#include "geometry/ShapeFactory.h"

namespace fig {

class ICanvas;
struct Palette;

// Верхняя панель-инвентарь: кнопка-иконка раскрывает список фигур, выбранную
// можно добавить на сцену кнопкой плюс
class Toolbar {
public:
    enum class Action { None, Consumed, AddShape };

    void draw(ICanvas& canvas, const Palette& pal) const;
    Action onClick(float px, float py);

    ShapeKind selectedKind() const { return selected_; }

private:
    bool open_ = false;
    ShapeKind selected_ = ShapeKind::Circle;
};

}  // namespace fig
