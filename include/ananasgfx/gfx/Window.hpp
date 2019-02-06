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

namespace gfx {

    class Application;

    class Window {
        friend class Application;
    public:
        static std::shared_ptr<Window> create(const WindowConfiguration& windowConfiguration) noexcept;

        virtual bool init() noexcept = 0;
        virtual bool shouldClose() noexcept = 0;
        virtual void makeContext() noexcept = 0;
        virtual void swapBuffers() noexcept = 0;

        const WindowConfiguration& getConfiguration() const noexcept;

        void addScene(std::shared_ptr<Scene> scene) noexcept;

        Renderer* getRenderer() noexcept;

        void tick(float dt) noexcept;

        TextureManager& getTextureManager() noexcept;

        unsigned int getWidth() const noexcept;
        unsigned int getHeight() const noexcept;

        const Camera& getCamera() const noexcept;
        const glm::mat4& getProjection2dMatrix() const noexcept;
        void setTemporaryProjection2dMatrix(const glm::mat4& matrix) noexcept;
        void removeTemporaryProjection2dMatrix() noexcept;

        std::optional<gfx::Scene*> getScene() const noexcept;

        font::FontManager& getFontManager() noexcept;

    protected:
        explicit Window(const WindowConfiguration& windowConfiguration) noexcept;
        void setRenderer(std::shared_ptr<Renderer> pRenderer) noexcept;

    protected:
        std::shared_ptr<Renderer> pRenderer;
        WindowConfiguration mConfiguration;
        std::stack<std::shared_ptr<Scene>> mSceneStack;
        unsigned int mWidth = 0;
        unsigned int mHeight = 0;
        float mHorizontalDpi = 0;
        float mVerticalDpi = 0;
        Camera mCamera;
        glm::mat4 mProjection2dMatrix;
        std::optional<glm::mat4> mTempProjection2dMatrix;
        TextureManager mTextureManager;
        font::FontManager mFontManager;
    };

}

#endif