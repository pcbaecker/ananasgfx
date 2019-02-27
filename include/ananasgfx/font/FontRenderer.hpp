#ifndef FONT_FONTRENDERER_H
#define FONT_FONTRENDERER_H

#include <string>
#include <vector>
#include <memory>

#include <glm/vec2.hpp>
#include <ananasgfx/gfx/Bitmap.hpp>
#include <ananasgfx/gfx/Defines.hpp>
#include "Font.hpp"

namespace font {

    /**
     * @brief Provides some methods to render fonts into a bitmap.
     */
    class FontRenderer {
    public:
        /**
         * @brief Converts the given utf8 string to a vector containing every char as a long.
         *
         * In case that a byte is invalid, it will be skipped.
         * @param string The given utf8 string to convert.
         * @return A vector containing a long for every utf8 char.
         */
        static std::vector<long> convert(const std::string& string) noexcept;
/*
        static std::shared_ptr<gfx::Bitmap> render(
                const std::string& text,
                Font* font,
                font::size_t fontSize,
                const glm::vec2& maxSize) noexcept;*/

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
    };

}

#endif