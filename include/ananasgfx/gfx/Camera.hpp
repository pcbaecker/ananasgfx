#ifndef GFX_CAMERA_H
#define GFX_CAMERA_H

#include <glm/glm.hpp>

namespace gfx {

    class Window;

    class Camera {
    public:
        Camera() noexcept;

        void updateWindow(Window* pWindow) noexcept;

        const glm::mat4& getViewProjectionMatrix() const noexcept;

    private:
        glm::mat4 mProjection;
        glm::mat4 mView;

        glm::mat4 mViewProjection;
    };

}

#endif