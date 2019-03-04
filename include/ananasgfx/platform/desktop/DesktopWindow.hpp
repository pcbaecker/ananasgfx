#ifndef PLATFORM_DESKTOP_WINDOW_H
#define PLATFORM_DESKTOP_WINDOW_H
#ifndef __ANDROID__

#include <GL/glew.h>
#include <ananasgfx/gfx/Window.hpp>
#include <GLFW/glfw3.h>
#include <optional>

namespace platform::desktop {

    /**
     * @brief Represents a window on a desktop device like a pc.
     */
    class DesktopWindow : public ::gfx::Window {
    public:
        /**
         * @brief Constructor.
         *
         * @param config The window configuration.
         */
        explicit DesktopWindow(const gfx::WindowConfiguration& config) noexcept;

        /**
         * @brief Destructor.
         */
        virtual ~DesktopWindow() noexcept;

        /**
         * @brief Initializes the desktop window.
         *
         * @return True on success.
         */
        bool init() noexcept override;

        /**
         * @brief Returns true if the window should close.
         *
         * @return True if the window should close.
         */
        bool shouldClose() noexcept override;

        /**
         * @brief Makes this window the current context.
         */
        void makeContext() noexcept override;

        /**
         * @brief Swaps the framebuffers.
         */
        void swapBuffers() noexcept override;

        /**
         * @brief Handles the events of this window.
         */
        void handleEvents() noexcept override;

    private:
        /**
         * @brief GLFW window handle.
         */
        GLFWwindow *pWindow = nullptr;

        /**
         * @brief Holds the current touch or empty if no touch is present.
         */
        std::optional<gfx::Touch> mTouch;
    };
}

#endif
#endif