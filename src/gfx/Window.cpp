#include <ananasgfx/gfx/Window.hpp>
#include <ananasgfx/platform/desktop/DesktopWindow.hpp>
#include <ananasgfx/platform/android/AndroidWindow.hpp>

namespace gfx {

#ifdef __UNITTEST__
    class UnittestWindow : public gfx::Window {
    public:
        UnittestWindow(const WindowConfiguration& windowConfiguration) noexcept : Window(windowConfiguration) {}
        bool init() noexcept override {return false;}
        bool shouldClose() noexcept override {return false;}
        void makeContext() noexcept override {}
        void swapBuffers() noexcept override {}
    };
#endif

    std::shared_ptr<Window> Window::create(const WindowConfiguration& windowConfiguration) noexcept {
#ifdef __ANDROID__
        return std::make_shared<platform::android::AndroidWindow>(windowConfiguration);
#elif __UNITTEST__
        return std::make_shared<UnittestWindow>(windowConfiguration);
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

    void Window::tick(float dt) noexcept {
        // Make sure that there is at least one scene
        if (!this->mSceneStack.empty()) {
            // Get the top scene
            auto& scene = this->mSceneStack.top();

            // Clear the scene
            this->pRenderer->clearScreen();

            // Call the scene update
            scene->update(dt);

            // Call the scene draw
            scene->draw();
        }
    }

    const glm::mat4 &Window::getProjection2dMatrix() const noexcept {
        if (this->mTempProjection2dMatrix.has_value()) {
            return *this->mTempProjection2dMatrix;
        } else {
            return this->mProjection2dMatrix;
        }
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

    void Window::setTemporaryProjection2dMatrix(const glm::mat4 &matrix) noexcept {
        this->mTempProjection2dMatrix = matrix;
    }

    void Window::removeTemporaryProjection2dMatrix() noexcept {
        this->mTempProjection2dMatrix.reset();
    }

    std::optional<gfx::Scene *> Window::getScene() const noexcept {
        if (this->mSceneStack.empty()) {
            return std::nullopt;
        } else {
            return this->mSceneStack.top().get();
        }
    }
}