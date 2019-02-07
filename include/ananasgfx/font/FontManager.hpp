#ifndef FONT_FONTMANAGER_H
#define FONT_FONTMANAGER_H

#include <vector>
#include <ee/Exception.hpp>

#include "Font.hpp"

// Forward declaration
typedef struct FT_LibraryRec_ *FT_Library;
typedef struct FT_FaceRec_*  FT_Face;

namespace font {

    DEFINE_EXCEPTION(FontManagerException);

    class FontManager {
    public:
        /**
         * @brief Constructor.
         *
         * @throws ee::Exception
         */
        FontManager();

        /**
         * @brief Destructor.
         */
        virtual ~FontManager() noexcept;

        bool registerFont(const std::string& filename, const std::string& fontFamily = "", const std::string& subFamily = "") noexcept;

        /**
         * @brief Tries to read the fontFamily and FontSubFamily from the given font handle.
         *
         * @param face The freetype font handle.
         * @return On success a tuple containing the fontFamily and the FontSubFamily.
         */
        static std::optional<std::tuple<std::string,std::string>> readFontFamily(FT_Face face) noexcept;

        /**
         * @brief Returns a reference to the font cache.
         *
         * @return Reference to the font cache.
         */
        const std::vector<Font>& getFontFache() const noexcept;

        void setHorizontalDpi(unsigned short dpi) noexcept;

        void setVerticalDpi(unsigned short dpi) noexcept;

        std::optional<Font*> get(const std::string& family, const std::string& subfamily) noexcept;

    private:
        /**
         * @brief The horizontal dpi of the screen.
         */
        unsigned short mHorizontalDpi = 0;

        /**
         * @brief The vertical dpi of the screen.
         */
        unsigned short mVerticalDpi = 0;

        /**
         * @brief The library main handle that must be created at the beginning and destroyed at the end.
         */
        FT_Library mLibrary;

        /**
         * @brief This vector contains all cached fonts.
         */
        std::vector<Font> mFontCache;
    };

}

#endif