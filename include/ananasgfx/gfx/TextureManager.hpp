#ifndef GFX_TEXTUREMANAGER_H
#define GFX_TEXTUREMANAGER_H

#include <string>
#include <map>

#include "Texture.hpp"
#include "Renderer.hpp"

namespace gfx {

    class Window;

    class TextureManager {
        friend class Window;
    public:
        std::optional<Texture*> get(const std::string& filename) noexcept;

    private:
        void setRenderer(Renderer* pRenderer) noexcept;

    private:
        Renderer* pRenderer = nullptr;
        std::map<std::string,std::shared_ptr<Texture>> mTextureCache;
    };

}

#endif