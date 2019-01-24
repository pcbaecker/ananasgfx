#ifndef FONT_FONTRENDERER_H
#define FONT_FONTRENDERER_H

#include <string>
#include <vector>

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
    };

}

#endif