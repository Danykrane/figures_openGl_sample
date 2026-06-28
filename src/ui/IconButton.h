#pragma once

namespace fig {

class ICanvas;
struct Palette;

// Кнопка с векторной иконкой: корзина (удалить) или плюс (добавить)
class IconButton {
public:
    enum class Icon { Trash, Plus };

    explicit IconButton(Icon icon) : icon_(icon) {}

    void setBounds(float x, float y, float size);
    void setVisible(bool v) { visible_ = v; }
    bool visible() const { return visible_; }

    void draw(ICanvas& canvas, const Palette& pal) const;
    bool hitTest(float px, float py) const;

private:
    Icon icon_;
    float x_ = 0.0f, y_ = 0.0f, size_ = 44.0f;
    bool visible_ = true;
};

}  // namespace fig
