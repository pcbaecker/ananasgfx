#ifndef FONT_FONTRENDERER_H
#define FONT_FONTRENDERER_H

#include <string>
#include <vector>
#include <memory>
#include <list>

#include <glm/vec2.hpp>
#include <ananasgfx/gfx/Bitmap.hpp>
#include <ananasgfx/gfx/Defines.hpp>
#include "Font.hpp"

namespace font {

    class Character;

    /**
     * @brief Provides some methods to render fonts into a bitmap.
     */
    class FontRenderer {
    public:
        typedef struct {
            float maxOverBaseline = 0.0f;
            float maxUnderBaseline = 0.0f;
            float width = 0.0f;
            float height = 0.0f;
        } Constraints;

        typedef struct : public Constraints {
            std::list<Character*> characters;
        } Chunk;

        /**
         * @brief Converts the given utf8 string to a vector containing every char as a long.
         *
         * In case that a byte is invalid, it will be skipped.
         * @param string The given utf8 string to convert.
         * @return A vector containing a long for every utf8 char.
         */
        static std::vector<long> convert(const std::string& string) noexcept;

        static std::unique_ptr<gfx::Bitmap> render(
                const std::string& text,
                Font* font,
                font::size_t fontSize,
                const glm::vec2& maxSize) noexcept;

        /**
         * @brief Renders the given text into the given bitmap.
         *
         * @param text The text to render.
         * @param font The font to be used to render.
         * @param fontSize The fontsize to be used.
         * @param bitmap The bitmap to render in.
         * @param horizontalAlign The horizontal align.
         * @param verticalAlign The vertical align.
         */
        static void render(
                const std::string& text,
                Font* font,
                font::size_t fontSize,
                gfx::Bitmap& bitmap,
                gfx::HorizontalAlign horizontalAlign,
                gfx::VerticalAlign verticalAlign) noexcept;

        void render(const std::string& text, gfx::Bitmap& bitmap) noexcept;
        float getHeight(const std::string& text, float width) noexcept;
        float getWidth(const std::string& text, float height) noexcept;

        std::list<Character*> getCharacters(const std::string& text) noexcept;

        void setConstraints(Chunk& chunk) noexcept;

        void setHorizontalAlign(gfx::HorizontalAlign horizontalAlign) noexcept;
        void setVerticalAlign(gfx::VerticalAlign verticalAlign) noexcept;
        void setFont(Font* font) noexcept;
        void setFontSize(font::size_t fontSize) noexcept;
        void setMultiline(bool value) noexcept;

        std::list<Chunk> getRows(const std::list<Character*>& characters, float width) noexcept;

        void render(const Chunk& chunk, float yOffset, gfx::Bitmap& bitmap) noexcept;

    private:
        gfx::HorizontalAlign mHorizontalAlign = gfx::HorizontalAlign::Center;
        gfx::VerticalAlign mVerticalAlign = gfx::VerticalAlign::Middle;
        std::optional<Font*> mFont;
        font::size_t mFontSize = 12;
        bool mMultiline = false;
    };

}

#endif