#ifndef GFX_WINDOW_H
#define GFX_WINDOW_H

#include <string>
#include <optional>
#include <memory>
#include <stack>
#include <chrono>

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

        void tick() noexcept;

        TextureManager& getTextureManager() noexcept;

        unsigned int getWidth() const noexcept;
        unsigned int getHeight() const noexcept;

        const Camera& getCamera() const noexcept;
        const glm::mat4& getProjection2dMatrix() const noexcept;

    protected:
        explicit Window(const WindowConfiguration& windowConfiguration) noexcept;
        void setRenderer(std::shared_ptr<Renderer> pRenderer) noexcept;

    protected:
        std::chrono::steady_clock::time_point mLastUpdate = std::chrono::steady_clock::now();
        std::shared_ptr<Renderer> pRenderer;
        WindowConfiguration mConfiguration;
        std::stack<std::shared_ptr<Scene>> mSceneStack;
        unsigned int mWidth = 0;
        unsigned int mHeight = 0;
        Camera mCamera;
        glm::mat4 mProjection2dMatrix;
        TextureManager mTextureManager;
    };

}

#endif