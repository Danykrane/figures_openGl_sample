#pragma once

#include <memory>
#include <stdexcept>
#include <string>

namespace fig {

class Scene;

// Ошибка создания окна или контекста OpenGL
class WindowError : public std::runtime_error {
public:
    explicit WindowError(const std::string& msg) : std::runtime_error(msg) {}
};

// Окно OpenGL по идиоме PIMPL: GLFW и OpenGL скрыты в .cpp, поэтому остальной
// код не зависит от графического бэкенда; рисует сцену и интерфейс
class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool isOpen() const;
    void pollEvents();
    void render(Scene& scene);
    void setWorldSize(float width, float height);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}  // namespace fig
