#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_SFNT_NAMES_H
#include FT_TRUETYPE_IDS_H
#include <ananasgfx/font/FontManager.hpp>
#include <ee/Log.hpp>

namespace font {

    FontManager::FontManager() {
        // Try to initialize the library
        FT_Error error = FT_Init_FreeType(&this->mLibrary);
        if (error != 0) {
            throw FontManagerException(__PRETTY_FUNCTION__, "Could not init FreeType", {
                ee::Note("FT_Error", error, __PRETTY_FUNCTION__)
            });
        }
    }

    FontManager::~FontManager() noexcept {
        // Clear the font cache (must be done to make sure all faces are freed before freeing the library)
        this->mFontCache.clear();

        // Free the library
        FT_Done_FreeType(this->mLibrary);
    }

    bool FontManager::registerFont(const std::string &filename, const std::string& fontFamily, const std::string& fontSubFamily) noexcept {
        // Try to open the file and read the font
        FT_Face face = nullptr;
        FT_Error error = FT_New_Face(this->mLibrary, filename.c_str(), 0, &face);
        if (error != 0) {
            ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Could not read font file", {
                ee::Note("Filename", filename, __PRETTY_FUNCTION__)
            }, ee::Stacktrace::create());
            return false;
        }

        // Try to set the charmap to unicode
        error = FT_Select_Charmap(face, ft_encoding_unicode);
        if (error != 0) {
            ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Could not select charmap", {
                    ee::Note("Filename", filename, __PRETTY_FUNCTION__)
            }, ee::Stacktrace::create());
            FT_Done_Face(face);
            return false;
        }

        // Check if font family and fontSubFamily is predefined
        if (!fontFamily.empty() && !fontSubFamily.empty()) {
            // Create the font object in cache
            this->mFontCache.emplace_back(face, fontFamily, fontSubFamily);
            return true;
        }

        // No font family name provided, we have to read the one from the file
        auto familyName = readFontFamily(face);
        if (!familyName.has_value() || std::get<0>(*familyName).empty() || std::get<1>(*familyName).empty()) {
            // Some required values are missing, we can not store this font
            FT_Done_Face(face);
            return false;
        }

        // create the font object in cache
        this->mFontCache.emplace_back(face, std::get<0>(*familyName), std::get<1>(*familyName));
        return true;
    }

    std::optional<std::tuple<std::string, std::string>> FontManager::readFontFamily(FT_Face face) noexcept {
        std::string fontFamily;
        std::string fontSubFamily;

        // Read the number of string inside the font file
        auto numberOfNames = FT_Get_Sfnt_Name_Count(face);

        // Iterate through all strings
        for (FT_UInt i = 0; i < numberOfNames; i++) {
            // Try to read this entry
            FT_SfntName name;
            auto error = FT_Get_Sfnt_Name(face, i, &name);
            if (error != 0) {
                // Just skip if something will no work
                continue;
            }

            // For some reason other platform types are not readable
            if (name.platform_id != TT_PLATFORM_MACINTOSH) {
                continue;
            }

            // Transform the c string
            std::string str((char*)name.string, name.string_len);

            // Handle the result depending on the type
            switch (name.name_id) {
                default:
                    // Ignore all other types
                    break;

                case TT_NAME_ID_FONT_FAMILY:
                    fontFamily = str;
                    break;
                case TT_NAME_ID_FONT_SUBFAMILY:
                    fontSubFamily = str;
                    break;
            }
        }

        // If not all required information is read, we return null
        if (fontFamily.empty() || fontSubFamily.empty()) {
            return std::nullopt;
        }

        // Return the font family and the font sub family
        return std::make_tuple(fontFamily, fontSubFamily);
    }

    const std::vector<Font> &FontManager::getFontFache() const noexcept {
        return this->mFontCache;
    }

    std::optional<Font *> FontManager::get(const std::string &family, const std::string &subfamily) noexcept {
        // Try to find font
        for (auto& font : this->mFontCache) {
            if (font.getFamilyName() == family && font.getSubFamilyName() == subfamily) {
                return &font;
            }
        }

        // No matching font found
        return std::nullopt;
    }
}