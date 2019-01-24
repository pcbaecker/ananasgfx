#include <ananasgfx/d2/Sprite.hpp>
#include <ananasgfx/gfx/Window.hpp>

namespace d2 {

    bool Sprite::init() noexcept {
        // Check if we already got a texture
        if (this->pTexture == nullptr) {
            // Try to load the texture for the given filename
            auto texture = this->pWindow->getTextureManager().get(this->mFilename);
            if (!texture.has_value()) {
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
        texCoords.set(0, 1.0f, 0.0f);

        // Upper right
        texCoords.set(1, 0.0f, 0.0f);

        // Lower right
        texCoords.set(2, 0.0f, 1.0f);

        // Lower left
        texCoords.set(3, 1.0f, 1.0f);
    }

    void Sprite::draw() noexcept {
        this->pWindow->getRenderer()->bindTexture(this->pTexture->getName());
        VertexNode::draw();
    }
}