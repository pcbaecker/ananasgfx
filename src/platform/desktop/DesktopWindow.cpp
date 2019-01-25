#if !defined(__ANDROID__) && !defined(__UNITTEST__)

#include <ananasgfx/platform/desktop/DesktopWindow.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ee/Log.hpp>

namespace platform::desktop {

    DesktopWindow::DesktopWindow(const gfx::WindowConfiguration &config) noexcept : Window(config) {

    }

    DesktopWindow::~DesktopWindow() noexcept {
        // Destroy window
        glfwDestroyWindow(this->pWindow);
        this->pWindow = nullptr;
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
            ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Could not create glfw window", {
                ee::Note("Width", this->getConfiguration().getWidth(), __PRETTY_FUNCTION__),
                ee::Note("Height", this->getConfiguration().getHeight(), __PRETTY_FUNCTION__),
                ee::Note("Title", this->getConfiguration().getTitle(), __PRETTY_FUNCTION__)
            });
            return false;
        }

        // Make this window the current context (at least during initialization)
        glfwMakeContextCurrent(this->pWindow);

        // Activate v-sync (limit framerate to monitor rate (normally 60 fps))
        glfwSwapInterval(1);

        // For some reason we have to use glew
        glewExperimental = GL_TRUE;//< Required for travis ci execution (xvfb)
        if (glewInit() != GLEW_OK) {
            ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Could not init glew", {
                    ee::Note("Width", this->getConfiguration().getWidth(), __PRETTY_FUNCTION__),
                    ee::Note("Height", this->getConfiguration().getHeight(), __PRETTY_FUNCTION__),
                    ee::Note("Title", this->getConfiguration().getTitle(), __PRETTY_FUNCTION__)
            });
            return false;
        }

        // Get Real window resolution
        int width, height;
        glfwGetFramebufferSize(this->pWindow, &width, &height);
        this->mWidth = static_cast<unsigned int>(width);
        this->mHeight = static_cast<unsigned int>(height);

        // Update camera
        this->mCamera.updateWindow(this);
        this->mProjection2dMatrix = glm::ortho(
                0.0f,
                static_cast<float>(this->mWidth),
                static_cast<float>(this->mHeight),
                0.0f);

        // Window successfully created
        ee::Log::log(ee::LogLevel::Info, "", __PRETTY_FUNCTION__, "Window created", {
                ee::Note("Width", this->mWidth),
                ee::Note("Height", this->mHeight)
        });
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