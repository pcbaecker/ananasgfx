#ifndef FONT_FONT_H
#define FONT_FONT_H

#include <map>
#include <string>

#include "Character.hpp"

// Forward declaration
typedef struct FT_FaceRec_*  FT_Face;

namespace font {

    typedef unsigned short size_t;

    /**
     * @brief Manages the creation and storage of the characters for a single font-family.
     */
    class Font {
    public:
        /**
         * @brief Constructor.
         *
         * @param face The freetype face handle.
         * @param familyName The font family name.
         * @param subFamilyName The sub font family name.
         */
        Font(FT_Face face, const std::string& familyName, const std::string& subFamilyName) noexcept;

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
         * @brief Returns a reference to the character cache map.
         *
         * @return Referemce to the character cache map.
         */
        const std::map<font::size_t,std::map<long,std::shared_ptr<Character>>>& getCharacterCache() const noexcept;

        /**
         * @brief Creates a character object for the given character and a specific font size.
         *
         * @param character The character to create the object for.
         * @param fontSize The font size.
         * @return True on success
         */
        std::optional<Character*> createCharacter(long character, font::size_t fontSize) noexcept;

        /**
         * @brief TODO
         * @param character
         * @return
         */
        std::optional<Character*> getCharacter(long character, font::size_t fontSize) noexcept;

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
         * @brief Holds the different characters for the different font sizes
         */
        std::map<font::size_t,std::map<long,std::shared_ptr<Character>>> mCharacterCache;
    };

}

#endif