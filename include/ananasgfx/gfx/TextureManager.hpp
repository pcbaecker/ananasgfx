#ifndef GFX_TEXTUREMANAGER_H
#define GFX_TEXTUREMANAGER_H

#include <string>
#include <map>

#include "Texture.hpp"
#include "Renderer.hpp"

namespace gfx {

    class Window;

    /**
     * @brief Manages and caches the different textures.
     */
    class TextureManager {
        friend class Window;
    public:
        /**
         * @brief Tries to find a texture with the given filename.
         *
         * Will try to find the requested image file in cache or otherwise try to open the image file.
         * @param filename The filename we want to lookup.
         * @return Optional that can contain a pointer to the texture.
         */
        std::optional<Texture*> get(const std::string& filename) noexcept;

    private:
        /**
         * @brief Sets the renderer.
         *
         * @param pRenderer The renderer.
         */
        void setRenderer(Renderer* pRenderer) noexcept;

    private:
        /**
         * @brief The renderer.
         */
        Renderer* pRenderer = nullptr;

        /**
         * @brief The texture cache map.
         */
        std::map<std::string,std::shared_ptr<Texture>> mTextureCache;
    };

}

#endif