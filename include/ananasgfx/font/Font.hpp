#ifndef FONT_FONT_H
#define FONT_FONT_H

#include <map>
#include <string>

#include "Character.hpp"

// Forward declaration
typedef struct FT_FaceRec_*  FT_Face;

namespace font {

    typedef unsigned short size_t;

    class Font {
    public:
        /**
         * @brief Constructor.
         *
         * @param face The freetype face handle.
         * @param familyName The font family name.
         * @param subFamilyName The sub font family name.
         * @param verticalDpi The vertical screen dpi.
         * @param horizontalDpi The horizontal screen dpi.
         */
        Font(FT_Face face, const std::string& familyName, const std::string& subFamilyName, unsigned short horizontalDpi, unsigned short verticalDpi) noexcept;

        /**
         * @brief Destructor.
         */
        virtual ~Font() noexcept;

        /**
         * @brief Returns the font family name.
         *
         * @return The font family name.
         */
        const std::string& getFamilyName() const noexcept;

        /**
         * @brief Returns the sub font family name.
         *
         * @return The sub font family.
         */
        const std::string& getSubFamilyName() const noexcept;

        /**
         * @brief Returns the vertical dpi.
         *
         * @return Vertical dpi.
         */
        unsigned short getVerticalDpi() const noexcept;

        /**
         * @brief Returns the horizontal dpi
         * @return
         */
        unsigned short getHorizontalDpi() const noexcept;

        /**
         * @brief Returns a reference to the character cache map.
         *
         * @return Referemce to the character cache map.
         */
        const std::map<font::size_t,std::map<long,Character>>& getCharacterCache() const noexcept;

        /**
         * @brief Creates a character object for the given character and a specific font size.
         *
         * @param character The character to create the object for.
         * @param fontSize The font size.
         * @return True on success
         */
        bool createCharacter(long character, font::size_t fontSize) noexcept;

    private:
        /**
         * @brief The face handle from freetype.
         */
        FT_Face mFaceHandle = nullptr;

        /**
         * @brief The font family name. (e.g.: Arial)
         */
        std::string mFamilyName;

        /**
         * @brief The font sub family name. (e.g.: Italic)
         */
        std::string mSubFamilyName;

        /**
         * @brief Holds the horizontal dpi.
         */
        unsigned short mHorizontalDpi = 0;

        /**
         * @brief Holds the vertical dpi.
         */
        unsigned short mVerticalDpi = 0;

        /**
         * @brief Holds the different characters for the different font sizes
         */
        std::map<font::size_t,std::map<long,Character>> mCharacterCache;
    };

}

#endif