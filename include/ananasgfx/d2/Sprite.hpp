#ifndef D2_SPRITE_H
#define D2_SPRITE_H

#include <ananasgfx/gfx/Texture.hpp>

#include "Rectangle.hpp"

namespace d2 {

    class Sprite : public Rectangle {
    public:
        bool init() noexcept override;

        void updateVertices() noexcept override;

        gfx::Shader *shader() noexcept override;

        void setFilename(const std::string& filename) noexcept;
        void setTexture(gfx::Texture* pTexture) noexcept;
        void setVerticalFlip(bool flip) noexcept;

        void draw() noexcept override;

    private:
        std::string mFilename;
        gfx::Texture* pTexture = nullptr;
        bool mVerticalFlip = false;
    };

}

#endif