#include <ananasgfx/gfx/Window.hpp>
#include <ananasgfx/platform/desktop/DesktopWindow.hpp>
#include <ananasgfx/platform/android/AndroidWindow.hpp>

namespace gfx {

    std::shared_ptr<Window> Window::create(const WindowConfiguration& windowConfiguration) noexcept {
#ifdef __ANDROID__
        return std::make_shared<platform::android::AndroidWindow>(windowConfiguration);
#elif __UNITTEST__
        return nullptr;
#else
        return std::make_shared<platform::desktop::DesktopWindow>(windowConfiguration);
#endif
    }

    void Window::addScene(std::shared_ptr<Scene> scene) noexcept {
        // Every scene needs a pointer to this window, because the scene will be rendered inside this window
        scene->pWindow = this;

        // Put scene on the scene stack
        this->mSceneStack.push(scene);
    }

    const WindowConfiguration &Window::getConfiguration() const noexcept {
        return this->mConfiguration;
    }

    Renderer *Window::getRenderer() noexcept {
        return this->pRenderer.get();
    }

    void Window::tick() noexcept {
        // Calculate delta time
        float delta = std::chrono::duration<float, std::ratio<1>>(std::chrono::steady_clock::now() - this->mLastUpdate).count();
        this->mLastUpdate = std::chrono::steady_clock::now();

        // Make sure that there is at least one scene
        if (!this->mSceneStack.empty()) {
            // Get the top scene
            auto& scene = this->mSceneStack.top();

            this->pRenderer->clearScreen();
            scene->update(delta);
            scene->draw();
        }
    }

    const glm::mat4 &Window::getProjection2dMatrix() const noexcept {
        return this->mProjection2dMatrix;
    }

    Window::Window(const WindowConfiguration &windowConfiguration) noexcept : mConfiguration(windowConfiguration) {

    }

    unsigned int Window::getWidth() const noexcept {
        return this->mWidth;
    }

    unsigned int Window::getHeight() const noexcept {
        return this->mHeight;
    }

    const Camera &Window::getCamera() const noexcept {
        return this->mCamera;
    }

    TextureManager &Window::getTextureManager() noexcept {
        return this->mTextureManager;
    }

    void Window::setRenderer(std::shared_ptr<Renderer> pRenderer) noexcept {
        this->pRenderer = std::move(pRenderer);
        this->mTextureManager.setRenderer(this->pRenderer.get());
    }
}