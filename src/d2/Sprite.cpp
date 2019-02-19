#include <ananasgfx/d2/Sprite.hpp>
#include <ananasgfx/gfx/Window.hpp>
#include <ee/Log.hpp>

namespace d2 {

    bool Sprite::init() noexcept {
        // Check if we already got a texture
        if (this->pTexture == nullptr) {
            if (this->mFilename.empty()) {
                ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "No texture or filename provided", {});
                return false;
            }

            // Try to load the texture for the given filename
            auto texture = this->pWindow->getTextureManager().get(this->mFilename);
            if (!texture.has_value()) {
                ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "Could not open file", {
                    ee::Note("Filename", this->mFilename)
                });
                return false;
            }

            // Texture found, we store a pointer to it
            this->pTexture = *texture;
        }

        // If no size is set, we use the default size of the texture
        if (this->mSize.x < 0.5f && this->mSize.y < 0.5f) {
            this->setSize(static_cast<float>(this->pTexture->getWidth()), static_cast<float>(this->pTexture->getHeight()));
        }

        return Rectangle::init();
    }

    void Sprite::setFilename(const std::string &filename) noexcept {
        this->mFilename = filename;
    }

    void Sprite::setTexture(gfx::Texture *pTexture) noexcept {
        this->pTexture = pTexture;
    }

    void Sprite::setVerticalFlip(bool flip) noexcept {
        this->mVerticalFlip = flip;

        if (isInitialized()) {
            this->updateVertices();
            this->pWindow->getRenderer()->bufferVertices(&this->mVertices);
        }
    }

    gfx::Shader *Sprite::shader() noexcept {
        if (this->pTexture) {
            return this->getWindow()->getRenderer()->getShader(this->pTexture->getShaderType());
        }
        return nullptr;
    }

    void Sprite::updateVertices() noexcept {
        Rectangle::updateVertices();
        auto& texCoords = this->mVertices.createBuffer(gfx::VertexType::TextureCoords, 2, 1);

        // Upper left
        texCoords.set(0, 0.0f, this->mVerticalFlip ? 1.0f : 0.0f);

        // Upper right
        texCoords.set(1, 1.0f, this->mVerticalFlip ? 1.0f : 0.0f);

        // Lower right
        texCoords.set(2, 1.0f, this->mVerticalFlip ? 0.0f : 1.0f);

        // Lower left
        texCoords.set(3, 0.0f, this->mVerticalFlip ? 0.0f : 1.0f);
    }

    void Sprite::draw() noexcept {
        this->pWindow->getRenderer()->bindTexture(this->pTexture->getName());
        VertexNode::draw();
    }
}