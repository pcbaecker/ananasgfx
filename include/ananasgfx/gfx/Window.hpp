#ifndef GFX_WINDOW_H
#define GFX_WINDOW_H

#include <string>
#include <optional>
#include <memory>
#include <stack>

#include <ananasgfx/font/FontManager.hpp>

#include "WindowConfiguration.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "TextureManager.hpp"
#include "FileManager.hpp"
#include "Touch.hpp"

namespace gfx {

    class Application;

    DEFINE_EXCEPTION(WindowException);

    /**
     * @brief Base window class that handles all common window things.
     */
    class Window {
        friend class Application;
    public:
        /**
         * @brief Creates a window based on the provided configuration.
         *
         * @param windowConfiguration The window configuration.
         * @return Shared pointer to the newly generated window.
         */
        static std::shared_ptr<Window> create(const WindowConfiguration& windowConfiguration) noexcept;

        /**
         * @brief Initializes the window.
         *
         * @return True on success.
         */
        virtual bool init() noexcept = 0;

        /**
         * @brief Returns true if the window should close.
         *
         * @return True if the window should close.
         */
        virtual bool shouldClose() noexcept = 0;

        /**
         * @brief Makes this window the current context.
         */
        virtual void makeContext() noexcept = 0;

        /**
         * @brief Swaps the framebuffers.
         */
        virtual void swapBuffers() noexcept = 0;

        /**
         * @brief Handles the window events.
         */
        virtual void handleEvents() noexcept = 0;

        /**
         * @brief Returns the window configuration.
         *
         * @return The window configuration.
         */
        const WindowConfiguration& getConfiguration() const noexcept;

        /**
         * @brief Adds a new scene to the window.
         *
         * @param scene The new scene.
         */
        void addScene(std::shared_ptr<Scene> scene) noexcept;

        /**
         * @brief Returns the renderer that is used in this window.
         *
         * @return The renderer.
         */
        Renderer* getRenderer() noexcept;

        /**
         * @brief Performs a new tick on this window.
         *
         * @param dt The delta time since last tick().
         */
        void tick(float dt) noexcept;

        /**
         * @brief Returns the texture manager of this window.
         *
         * @return The texture manager of this window.
         */
        TextureManager& getTextureManager() noexcept;

        /**
         * @brief Returns the width of this window.
         *
         * @return The width of this window.
         */
        unsigned int getWidth() const noexcept;

        /**
         * @brief Returns the height of this window.
         *
         * @return The height of this window.
         */
        unsigned int getHeight() const noexcept;

        /**
         * @brief Returns the camera of this window.
         *
         * @return The camera.
         */
        const Camera& getCamera() const noexcept;

        /**
         * @brief Returns the 2d projection matrix.
         *
         * @return The 2d projection matrix.
         */
        const glm::mat4& getProjection2dMatrix() const noexcept;

        /**
         * @brief Sets a temporary 2d projection matrix.
         *
         * @param matrix The temporary 2d projection matrix.
         */
        void setTemporaryProjection2dMatrix(const glm::mat4& matrix) noexcept;

        /**
         * @brief Removes the temporary 2d projection matrix.
         */
        void removeTemporaryProjection2dMatrix() noexcept;

        /**
         * @brief Returns the current scene or empty if no scene is active.
         *
         * @return Optional that can contain the current scene.
         */
        std::optional<gfx::Scene*> getScene() const noexcept;

        /**
         * @brief Returns the font manager of this window.
         *
         * @return The font manager of this window.
         */
        font::FontManager& getFontManager() noexcept;

        /**
         * @brief Returns the file manager of this window.
         *
         * @return The file manager of this window.
         */
        const FileManager& getFileManager() const;

        /**
         * @brief Returns the vertical dpi.
         *
         * @return The vertical dpi.
         */
        float getVerticalDpi() const noexcept;

        /**
         * @brief Returns the horizontal dpi.
         *
         * @return The horizontal dpi.
         */
        float getHorizontalDpi() const noexcept;

    protected:
        /**
         * @brief The hidden constructor.
         *
         * @param windowConfiguration The window configuration.
         */
        explicit Window(const WindowConfiguration& windowConfiguration) noexcept;

        /**
         * @brief Sets the renderer.
         *
         * @param pRenderer The renderer.
         */
        void setRenderer(std::shared_ptr<Renderer> pRenderer) noexcept;

        /**
         * @brief Is called when a touch begins.
         *
         * @param touch The touch that began.
         */
        void onTouchBegan(const Touch& touch) noexcept;

        /**
         * @brief Is called when a touch moves.
         *
         * @param touch The touch moved.
         */
        void onTouchMoved(const Touch& touch) noexcept;

        /**
         * @brief Is called when a touch ended.
         *
         * @param touch The touch ended.
         */
        void onTouchEnded(const Touch& touch) noexcept;

    protected:
        /**
         * @brief The renderer of this window.
         */
        std::shared_ptr<Renderer> pRenderer;

        /**
         * @brief The window configuration.
         */
        WindowConfiguration mConfiguration;

        /**
         * @brief The scene stack.
         */
        std::stack<std::shared_ptr<Scene>> mSceneStack;

        /**
         * @brief The width of the window.
         */
        unsigned int mWidth = 0;

        /**
         * @brief The height of the window.
         */
        unsigned int mHeight = 0;

        /**
         * @brief The horizontal dpi.
         */
        float mHorizontalDpi = 0;

        /**
         * @brief The vertical dpi.
         */
        float mVerticalDpi = 0;

        /**
         * @brief The camera.
         */
        Camera mCamera;

        /**
         * @brief The 2d projection matrix.
         */
        glm::mat4 mProjection2dMatrix;

        /**
         * @brief A temporary 2d projection matrix.
         */
        std::optional<glm::mat4> mTempProjection2dMatrix;

        /**
         * @brief The texture manager.
         */
        TextureManager mTextureManager;

        /**
         * @brief The font manager.
         */
        font::FontManager mFontManager;

        /**
         * @brief The filemanager.
         */
        std::shared_ptr<FileManager> mFileManager;
    };
}

#endif