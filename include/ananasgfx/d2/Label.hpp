#ifndef D2_LABEL_H
#define D2_LABEL_H

#include "Sprite.hpp"

namespace d2 {

    class Label : public Sprite {
    public:
        bool init() noexcept override;

        void setText(std::string text) noexcept;
        const std::string& getText() const noexcept;

    private:
        std::string mText;
        std::shared_ptr<gfx::Texture> mTexture;
    };

}

#endif