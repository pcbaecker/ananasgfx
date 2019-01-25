#ifndef PLATFORM_DESKTOP_WINDOW_H
#define PLATFORM_DESKTOP_WINDOW_H
#ifndef __ANDROID__

#include <GL/glew.h>
#include <ananasgfx/gfx/Window.hpp>
#include <GLFW/glfw3.h>

namespace platform::desktop {

    class DesktopWindow : public ::gfx::Window {
    public:
        explicit DesktopWindow(const gfx::WindowConfiguration& config) noexcept;

        virtual ~DesktopWindow() noexcept;

        bool init() noexcept override;

        bool shouldClose() noexcept override;

        void makeContext() noexcept override;

        void swapBuffers() noexcept override;

    private:
        GLFWwindow *pWindow = nullptr;
    };

}

#endif
#endif