#include <glm/gtc/matrix_transform.hpp>
#include <ananasgfx/gfx/Camera.hpp>
#include <ananasgfx/gfx/Window.hpp>

namespace gfx {

    Camera::Camera() noexcept {
        this->mView = glm::lookAt(
                glm::vec3(3,3,3), // Camera is at (4,3,3), in World Space
                glm::vec3(0,0,0), // and looks at the origin
                glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
        );
    }

    void Camera::updateWindow(gfx::Window *pWindow) noexcept {
        this->mProjection = glm::perspective(glm::radians(45.0f), (float) pWindow->getWidth() / (float)pWindow->getHeight(), 0.1f, 100.0f);
        this->mViewProjection = this->mProjection * this->mView;
    }

    const glm::mat4 &Camera::getViewProjectionMatrix() const noexcept {
        return this->mViewProjection;
    }
}