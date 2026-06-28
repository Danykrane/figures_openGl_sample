#include "render/Window.h"

#if defined(__APPLE__)
#define GL_SILENCE_DEPRECATION
#endif
#include <GLFW/glfw3.h>

#include <vector>

#include "geometry/ShapeFactory.h"
#include "render/OpenGLCanvas.h"
#include "scene/Palette.h"
#include "scene/Scene.h"
#include "ui/IconButton.h"
#include "ui/ThemeButton.h"
#include "ui/Toolbar.h"

namespace fig {

namespace {

bool pointInPolygon(Point2D p, const std::vector<Point2D>& poly) {
    bool inside = false;
    const std::size_t n = poly.size();
    for (std::size_t i = 0, j = n - 1; i < n; j = i++) {
        const Point2D& a = poly[i];
        const Point2D& b = poly[j];
        if (((a.y > p.y) != (b.y > p.y)) &&
            (p.x < (b.x - a.x) * (p.y - a.y) / (b.y - a.y) + a.x)) {
            inside = !inside;
        }
    }
    return inside;
}

}  // namespace

struct Window::Impl {
    GLFWwindow* window = nullptr;
    OpenGLCanvas canvas;
    Scene* scene = nullptr;

    ThemeButton themeButton;
    Toolbar toolbar;
    IconButton trash{IconButton::Icon::Trash};

    float worldW = 800.0f;
    float worldH = 600.0f;
    int selected = -1;
    int hovered = -1;
    bool dragging = false;
    double lastX = 0.0;
    double lastY = 0.0;
    int winW = 0, winH = 0, fbW = 0, fbH = 0;

    Palette pal() const { return paletteFor(themeButton.theme()); }

    bool shiftHeld() const {
        return glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
               glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
    }

    Point2D screenToWorld(double px, double py) const {
        return {static_cast<float>(px / winW * worldW),
                static_cast<float>((1.0 - py / winH) * worldH)};
    }

    int pick(double px, double py) const {
        if (scene == nullptr) {
            return -1;
        }
        const Point2D w = screenToWorld(px, py);
        for (int i = static_cast<int>(scene->size()) - 1; i >= 0; --i) {  // сверху вниз
            if (pointInPolygon(w, scene->at(static_cast<std::size_t>(i)).outline())) {
                return i;
            }
        }
        return -1;
    }

    void drawScene() {
        glViewport(0, 0, fbW, fbH);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, worldW, 0.0, worldH, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        const Palette p = pal();
        glClearColor(p.bg.r, p.bg.g, p.bg.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        scene->drawAll(canvas);
        const int count = static_cast<int>(scene->size());
        for (int i = 0; i < count; ++i) {
            Color edge = p.border;
            float width = 1.5f;
            if (i == selected) {
                edge = p.accent;
                width = 3.0f;
            } else if (i == hovered) {
                edge = p.accentHover;
                width = 2.0f;
            }
            canvas.strokePolyline(scene->at(static_cast<std::size_t>(i)).outline(), edge, width, true);
        }
    }

    void drawOverlay() {
        glViewport(0, 0, fbW, fbH);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, winW, winH, 0.0, -1.0, 1.0);  // экранные координаты, Y вниз
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        const Palette p = pal();
        const bool hasSel = scene != nullptr && selected >= 0 && selected < static_cast<int>(scene->size());

        trash.setVisible(hasSel);
        trash.setBounds(static_cast<float>(winW) - 64.0f, static_cast<float>(winH) - 64.0f, 44.0f);
        trash.draw(canvas, p);

        themeButton.layout(static_cast<float>(winW));
        themeButton.draw(canvas, p);
        toolbar.draw(canvas, p);
    }

    void renderFrame() {
        glfwGetFramebufferSize(window, &fbW, &fbH);
        glfwGetWindowSize(window, &winW, &winH);
        drawScene();
        drawOverlay();
    }

    void onMouseButton(int button, int action) {
        if (button != GLFW_MOUSE_BUTTON_LEFT) {
            return;
        }
        if (action == GLFW_RELEASE) {
            dragging = false;
            return;
        }
        double mx = 0, my = 0;
        glfwGetCursorPos(window, &mx, &my);
        const float px = static_cast<float>(mx);
        const float py = static_cast<float>(my);

        if (themeButton.onClick(px, py)) {
            return;
        }
        switch (toolbar.onClick(px, py)) {
            case Toolbar::Action::AddShape:
                if (scene != nullptr) {
                    const Color fill = kShapeColors[scene->size() % kShapeColors.size()];
                    scene->addShape(makeShape(toolbar.selectedKind(), {worldW * 0.5f, worldH * 0.5f}, fill));
                    selected = static_cast<int>(scene->size()) - 1;
                }
                return;
            case Toolbar::Action::Consumed:
                return;
            case Toolbar::Action::None:
                break;
        }

        const bool hasSel = scene != nullptr && selected >= 0 && selected < static_cast<int>(scene->size());
        if (hasSel && trash.hitTest(px, py)) {
            scene->removeAt(static_cast<std::size_t>(selected));
            selected = -1;
            hovered = -1;
            return;
        }

        const int hit = pick(mx, my);
        selected = hit;
        dragging = (hit >= 0 && shiftHeld());  // двигаем только с зажатым Shift
        lastX = mx;
        lastY = my;
    }

    void onCursorPos(double x, double y) {
        if (dragging && scene != nullptr && selected >= 0) {
            const float dx = static_cast<float>((x - lastX) / winW * worldW);
            const float dy = static_cast<float>(-(y - lastY) / winH * worldH);  // экран Y вниз
            scene->at(static_cast<std::size_t>(selected)).moveBy(dx, dy);
        } else {
            hovered = pick(x, y);
        }
        lastX = x;
        lastY = y;
    }
};

Window::Window(int width, int height, const std::string& title)
    : impl_(std::make_unique<Impl>()) {
    if (glfwInit() != GLFW_TRUE) {
        throw WindowError("glfwInit failed (no display?)");
    }
    glfwWindowHint(GLFW_SAMPLES, 4);  // сглаживание граней
    impl_->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (impl_->window == nullptr) {
        glfwTerminate();
        throw WindowError("failed to create OpenGL window");
    }

    glfwMakeContextCurrent(impl_->window);
    glfwSwapInterval(1);
    glfwSetWindowUserPointer(impl_->window, impl_.get());
    glfwSetMouseButtonCallback(impl_->window, [](GLFWwindow* w, int button, int action, int) {
        static_cast<Impl*>(glfwGetWindowUserPointer(w))->onMouseButton(button, action);
    });
    glfwSetCursorPosCallback(impl_->window, [](GLFWwindow* w, double x, double y) {
        static_cast<Impl*>(glfwGetWindowUserPointer(w))->onCursorPos(x, y);
    });

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_MULTISAMPLE);
}

Window::~Window() {
    if (impl_->window != nullptr) {
        glfwDestroyWindow(impl_->window);
        glfwTerminate();
    }
}

bool Window::isOpen() const {
    return impl_->window != nullptr && glfwWindowShouldClose(impl_->window) == 0;
}

void Window::pollEvents() {
    glfwPollEvents();
    if (glfwGetKey(impl_->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(impl_->window, GLFW_TRUE);
    }
}

void Window::render(Scene& scene) {
    impl_->scene = &scene;
    glfwMakeContextCurrent(impl_->window);
    impl_->renderFrame();
    glfwSwapBuffers(impl_->window);
}

void Window::setWorldSize(float width, float height) {
    impl_->worldW = width;
    impl_->worldH = height;
}

}  // namespace fig
