#if !defined(__ANDROID__) && !defined(__UNITTEST__)

#include <iostream>

#include <ananasgfx/platform/desktop/DesktopWindow.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace platform::desktop {

    DesktopWindow::DesktopWindow(const gfx::WindowConfiguration &config) noexcept : Window(config) {

    }

    bool DesktopWindow::init() noexcept {
        // Initalize the window
        this->pWindow = glfwCreateWindow(
                this->getConfiguration().getWidth(),
                this->getConfiguration().getHeight(),
                this->getConfiguration().getTitle().c_str(),
                nullptr,
                nullptr);
        if (this->pWindow == nullptr) {
            return false;
        }

        // Make this window the current context (at least during initialization)
        glfwMakeContextCurrent(this->pWindow);

        // Activate v-sync (limit framerate to monitor rate (normally 60 fps))
        glfwSwapInterval(1);

        // For some reason we have to use glew
        if (glewInit() != GLEW_OK) {
            std::cerr << __PRETTY_FUNCTION__ << ": Unable to init GLEW" << std::endl;
            return false;
        }

        // Get Real window resolution
        int width, height;
        glfwGetFramebufferSize(this->pWindow, &width, &height);
        this->mWidth = static_cast<unsigned int>(width);
        this->mHeight = static_cast<unsigned int>(height);
        std::cout << "Window size: " << this->mWidth << "x" << this->mHeight << std::endl;

        // Update camera
        this->mCamera.updateWindow(this);
        this->mProjection2dMatrix = glm::ortho(
                0.0f,
                static_cast<float>(this->mWidth),
                static_cast<float>(this->mHeight),
                0.0f);

        return true;
    }

    bool DesktopWindow::shouldClose() noexcept {
        return glfwWindowShouldClose(this->pWindow) == GLFW_TRUE;
    }

    void DesktopWindow::makeContext() noexcept {
        glfwMakeContextCurrent(this->pWindow);
    }

    void DesktopWindow::swapBuffers() noexcept {
        glfwSwapBuffers(this->pWindow);
        glfwPollEvents();
    }
}

#endif