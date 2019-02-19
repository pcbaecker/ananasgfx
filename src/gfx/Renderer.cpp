#include <ananasgfx/gfx/Renderer.hpp>
#include <ananasgfx/gfx/renderer/opengl/OpenglRenderer.hpp>

namespace gfx {

    std::shared_ptr<Renderer> Renderer::create() {
        try {
#ifdef __UNITTEST__
            return nullptr;
#else
            return std::make_shared<::gfx::renderer::opengl::OpenglRenderer>();
#endif
        } catch (ee::Exception& e) {
            throw;
        }
    }

}