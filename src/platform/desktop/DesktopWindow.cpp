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

        // Get dpi
        GLFWmonitor* pPrimaryMonitor = glfwGetPrimaryMonitor();
        int widthMM, heightMM;
        glfwGetMonitorPhysicalSize(pPrimaryMonitor, &widthMM, &heightMM);
        const GLFWvidmode* mode = glfwGetVideoMode(pPrimaryMonitor);
        this->mHorizontalDpi = mode->width / (widthMM / 25.4f);
        this->mVerticalDpi = mode->height / (heightMM / 25.4f);
#ifdef __APPLE__
        this->mHorizontalDpi *= 2.0f;
        this->mVerticalDpi *= 2.0f;
#endif

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
                ee::Note("Height", this->mHeight),
                ee::Note("hDPI", this->mHorizontalDpi),
                ee::Note("vDPI", this->mVerticalDpi)
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
    }

    void DesktopWindow::handleEvents() noexcept {
        glfwPollEvents();

        // Get cursor position
        double mx = 0.0, my = 0.0;
        glfwGetCursorPos(this->pWindow, &mx,&my);
#ifdef __APPLE__
        mx *= 2.0;
        my *= 2.0;
#endif

        // Calculate touch position
        //my = this->mHeight - my;

        //
        if (glfwGetMouseButton(this->pWindow, 0) == GLFW_PRESS) {
            if (!this->mTouch.has_value()) {
                this->mTouch.emplace(0, mx, my);
                this->mTouch->setLast(mx, my);
                this->onTouchBegan(*this->mTouch);
            } else if(static_cast<int>(mx) != static_cast<int>(this->mTouch->getLastX())
                   || static_cast<int>(my) != static_cast<int>(this->mTouch->getLastY())) {
                this->mTouch->setLast(mx, my);
                this->onTouchMoved(*this->mTouch);
            }
        } else {
            if (this->mTouch.has_value()) {
                this->mTouch->setLast(mx, my);
                this->onTouchEnded(*this->mTouch);
                this->mTouch.reset();
            }
        }
    }
}

#endif