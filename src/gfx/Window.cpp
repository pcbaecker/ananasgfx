#include <ananasgfx/gfx/Window.hpp>
#include <ananasgfx/platform/desktop/DesktopWindow.hpp>
#include <ananasgfx/platform/android/AndroidWindow.hpp>
#include <ee/Log.hpp>

namespace gfx {

#ifdef __UNITTEST__
    class UnittestWindow : public gfx::Window {
    public:
        UnittestWindow(const WindowConfiguration& windowConfiguration) noexcept : Window(windowConfiguration) {
            this->mWidth = 1;
            this->mHeight = 1;
        }
        bool init() noexcept override {return false;}
        bool shouldClose() noexcept override {return false;}
        void makeContext() noexcept override {}
        void swapBuffers() noexcept override {}
        void handleEvents() noexcept override {}
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

    void Window::addRootNode(std::shared_ptr<Node> rootNode) noexcept {
        // Every root node needs a pointer to this window, because the root node will be rendered inside this window
        rootNode->pWindow = this;

        // Put scene on the scene stack
        this->mRootNodeStack.push(rootNode);
    }

    const WindowConfiguration &Window::getConfiguration() const noexcept {
        return this->mConfiguration;
    }

    Renderer *Window::getRenderer() noexcept {
        return this->pRenderer.get();
    }

    void Window::tick(float dt) noexcept {
        // Make sure that there is at least one scene
        if (!this->mRootNodeStack.empty()) {
            // Get the top scene
            auto& scene = this->mRootNodeStack.top();

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

    font::FontManager &Window::getFontManager() noexcept {
        return this->mFontManager;
    }

    std::optional<gfx::Node *> Window::getRootNode() const noexcept {
        if (this->mRootNodeStack.empty()) {
            return {};
        } else {
            return this->mRootNodeStack.top().get();
        }
    }

    const FileManager &Window::getFileManager() const {
        // Make sure FileManager is set before
        if (!this->mFileManager) {
            throw WindowException(__PRETTY_FUNCTION__, "FileManager must be set before calling this method", {});
        }

        // Return a reference of the FileManager.
        return *this->mFileManager;
    }

    float Window::getVerticalDpi() const noexcept {
        return this->mVerticalDpi;
    }

    float Window::getHorizontalDpi() const noexcept {
        return this->mHorizontalDpi;
    }

    void Window::onTouchBegan(const Touch &touch) noexcept {
        //TRACE("Touch began", {ee::Note("X", touch.getLastX()),ee::Note("Y", touch.getLastY())});

        // Make sure a scene exists
        if (!this->mRootNodeStack.empty()) {
            // Get the top scene
            auto& scene = this->mRootNodeStack.top();

            // Propagate the touch to the scene
            scene->onTouchBegan(touch);
        }
    }

    void Window::onTouchMoved(const Touch &touch) noexcept {
        //TRACE("Touch moved", {ee::Note("X", touch.getLastX()),ee::Note("Y", touch.getLastY())});

        // Make sure a scene exists
        if (!this->mRootNodeStack.empty()) {
            // Get the top scene
            auto& scene = this->mRootNodeStack.top();

            // Propagate the touch to the scene
            scene->onTouchMoved(touch);
        }
    }

    void Window::onTouchEnded(const Touch &touch) noexcept {
        //TRACE("Touch ended", {ee::Note("X", touch.getLastX()),ee::Note("Y", touch.getLastY())});

        // Make sure a scene exists
        if (!this->mRootNodeStack.empty()) {
            // Get the top scene
            auto& scene = this->mRootNodeStack.top();

            // Propagate the touch to the scene
            scene->onTouchEnded(touch);
        }
    }

    Application *Window::getApplication() const noexcept {
        return this->pApplication;
    }

    void Window::setApplication(Application *application) noexcept {
        this->pApplication = application;
    }
}