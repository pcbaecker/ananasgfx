#include <ananasgfx/d2/Label.hpp>
#include <ananasgfx/font/FontRenderer.hpp>
#include <ananasgfx/gfx/Window.hpp>
#include <ee/Log.hpp>

namespace d2 {

    bool Label::init() noexcept {
        this->createBitmap();
        this->renderText();

        return Sprite::init();
    }

    void Label::renderText() noexcept {
        // Make sure a font is provided
        if (this->pFont == nullptr) {
            ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "Attempt to render text without a provided font", {});
            return;
        }

        // Make sure there is a bitmap
        if (!this->mBitmap) {
            ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Attempt to render text without a bitmap", {}, ee::Stacktrace::create());
            return;
        }

        // Clear the bitmap before rendering
        this->mBitmap->clear();

        // Render the text to the bitmap
        font::FontRenderer::render(this->mText, this->pFont, 24, *this->mBitmap, this->mHorizontalAlign, this->mVerticalAlign);

        // Convert the bitmap to a texture
        auto texture = gfx::Texture::create(this->pWindow->getRenderer(), *this->mBitmap);
        if (!texture.has_value()) {
            ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Could not convert the bitmap to a texture", {}, ee::Stacktrace::create());
            return;
        }

        // Store the new texture
        this->mTexture = *texture;
        this->setTexture(this->mTexture.get());
    }

    void Label::createBitmap() noexcept {
        // Create the new bitmap
        auto w = static_cast<unsigned short>(this->mSize.x);
        auto h = static_cast<unsigned short>(this->mSize.y);
        this->mBitmap = std::make_unique<gfx::Bitmap>(malloc(w*h), w, h, 1);
    }

    bool Label::setFont(const std::string &fontFamily, const std::string &fontSubFamily) noexcept {
        // Try to find the font
        auto font = this->pWindow->getFontManager().get(fontFamily, fontSubFamily);
        if (!font.has_value()) {
            ee::Log::log(ee::LogLevel::Trace, "", __PRETTY_FUNCTION__, "The requested font could not be found", {
                ee::Note("FontFamily", fontFamily),
                ee::Note("FontSubFamily", fontSubFamily)
            });
            return false;
        }

        // Font is found, we store it
        this->pFont = *font;

        // Render the text with the new font again
        if (isInitialized()) {
            this->renderText();
        }

        return true;
    }

    font::Font *Label::getFont() const noexcept {
        return this->pFont;
    }

    void Label::setText(std::string text) noexcept {
        this->mText = std::move(text);

        // Render the new text
        if (isInitialized()) {
            this->renderText();
        }
    }

    const std::string &Label::getText() const noexcept {
        return this->mText;
    }

    void Label::setHorizontalAlign(gfx::HorizontalAlign align) noexcept {
        this->mHorizontalAlign = align;

        // Render text with new alignment
        if (isInitialized()) {
            this->renderText();
        }
    }

    gfx::HorizontalAlign Label::getHorizontalAlign() const noexcept {
        return this->mHorizontalAlign;
    }

    void Label::setVerticalAlign(gfx::VerticalAlign align) noexcept {
        this->mVerticalAlign = align;

        // Render text with new alignment
        if (isInitialized()) {
            this->renderText();
        }
    }

    gfx::VerticalAlign Label::getVerticalAlign() const noexcept {
        return this->mVerticalAlign;
    }

    void Label::setSize(float x, float y) noexcept {
        Sprite::setSize(x, y);

        // We have to create a new bitmap for the new size
        if (isInitialized()) {
            this->createBitmap();
            this->renderText();
        }
    }
}