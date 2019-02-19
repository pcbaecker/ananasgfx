#include <ananasgfx/gfx/TextureManager.hpp>

namespace gfx {

    std::optional<Texture *> TextureManager::get(const std::string &filename) noexcept {
        // Check if we already cached the texture
        if (this->mTextureCache.count(filename) > 0) {
            // Return pointer of the texture
            return this->mTextureCache.at(filename).get();
        }

        // Try to create the texture
        auto texture = Texture::create(this->pRenderer, filename);
        if (!texture.has_value()) {
            // Could not load the texture for some reason
            return std::nullopt;
        }

        // Store the texture in the cache
        this->mTextureCache[filename] = *texture;

        // Return pointer to the texture
        return (*texture).get();
    }

    void TextureManager::setRenderer(Renderer *pRenderer) noexcept {
        this->pRenderer = pRenderer;
    }
}