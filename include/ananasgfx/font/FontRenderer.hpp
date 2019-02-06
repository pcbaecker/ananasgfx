#ifndef FONT_FONTRENDERER_H
#define FONT_FONTRENDERER_H

#include <string>
#include <vector>
#include <memory>

#include <glm/vec2.hpp>
#include <ananasgfx/gfx/Bitmap.hpp>
#include "Font.hpp"

namespace font {

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

        static std::shared_ptr<gfx::Bitmap> render(
                const std::string& text,
                Font* font,
                font::size_t fontSize,
                const glm::vec2& maxSize) noexcept;
    };

}

#endif