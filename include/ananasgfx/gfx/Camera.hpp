#ifndef GFX_CAMERA_H
#define GFX_CAMERA_H

#include <glm/glm.hpp>

namespace gfx {

    class Window;

    /**
     * @brief The base camera class that handles the 3d point of view.
     */
    class Camera {
    public:
        /**
         * @brief Constructor.
         */
        Camera() noexcept;

        /**
         * @brief Registers the window on this camera.
         *
         * @param pWindow The window to be registered.
         */
        void updateWindow(Window* pWindow) noexcept;

        /**
         * @brief Returns the view projection matrix.
         *
         * @return The view projection matrix.
         */
        const glm::mat4& getViewProjectionMatrix() const noexcept;

    private:
        /**
         * @brief The projection matrix.
         */
        glm::mat4 mProjection;

        /**
         * @brief The view matrix.
         */
        glm::mat4 mView;

        /**
         * @brief The view projection matrix.
         */
        glm::mat4 mViewProjection;
    };

}

#endif