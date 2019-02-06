#include <ananasgfx/font/Font.hpp>
#include <ee/Log.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

namespace font {

    Font::Font(FT_Face face, const std::string &familyName, const std::string &subFamilyName, unsigned short horizontalDpi, unsigned short verticalDpi) noexcept :
    mFaceHandle(face), mFamilyName(familyName), mSubFamilyName(subFamilyName), mHorizontalDpi(horizontalDpi), mVerticalDpi(verticalDpi) {

    }

    Font::~Font() noexcept {
        if (this->mFaceHandle) {
            FT_Done_Face(this->mFaceHandle);
        }
    }

    const std::string &Font::getFamilyName() const noexcept {
        return this->mFamilyName;
    }

    const std::string &Font::getSubFamilyName() const noexcept {
        return this->mSubFamilyName;
    }

    unsigned short Font::getVerticalDpi() const noexcept {
        return this->mVerticalDpi;
    }

    unsigned short Font::getHorizontalDpi() const noexcept {
        return this->mHorizontalDpi;
    }

    const std::map<font::size_t, std::map<long, Character>> &Font::getCharacterCache() const noexcept {
        return this->mCharacterCache;
    }

    std::optional<Character*> Font::createCharacter(long character, font::size_t fontSize) noexcept {
        // Get cache for this font size
        auto& cache = this->mCharacterCache[fontSize];

        // Make sure that we havent already created an object for this character
        if (cache.count(character)) {
            ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "Object for this char already created", {
                ee::Note("Character", character, __PRETTY_FUNCTION__),
                ee::Note("Fontsize", fontSize, __PRETTY_FUNCTION__)
            }, ee::Stacktrace::create());
            return std::nullopt;
        }

        // Set font size
        FT_Error error = FT_Set_Char_Size(this->mFaceHandle, 0, fontSize*64, this->mHorizontalDpi, this->mVerticalDpi);
        if (error) {
            ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Could not set char size", {
                    ee::Note("Character", character, __PRETTY_FUNCTION__),
                    ee::Note("Fontsize", fontSize, __PRETTY_FUNCTION__)
            }, ee::Stacktrace::create());
            return std::nullopt;
        }

        // Get Glyph index
        FT_UInt glyph_index = FT_Get_Char_Index(this->mFaceHandle, static_cast<FT_ULong>(character));

        // Load glyph
        error = FT_Load_Glyph(this->mFaceHandle, glyph_index, FT_LOAD_DEFAULT);
        if (error) {
            ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Could not load glyph", {
                    ee::Note("Character", character, __PRETTY_FUNCTION__),
                    ee::Note("Fontsize", fontSize, __PRETTY_FUNCTION__)
            }, ee::Stacktrace::create());
            return std::nullopt;
        }

        // Load glyph
        FT_Glyph glyph;
        error = FT_Get_Glyph(this->mFaceHandle->glyph, &glyph);
        if (error || !glyph) {
            ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Could not get glyph", {
                    ee::Note("Character", character, __PRETTY_FUNCTION__),
                    ee::Note("Fontsize", fontSize, __PRETTY_FUNCTION__)
            }, ee::Stacktrace::create());
            return std::nullopt;
        }

        // Get bounding box
        FT_BBox box;
        FT_Glyph_Get_CBox(glyph, FT_GLYPH_BBOX_PIXELS, &box);

        // Render bitmap
        FT_Vector vec = {0,0};
        error = FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, &vec, true);
        if (error) {
            FT_Done_Glyph(glyph);
            ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Could not generate bitmap", {
                    ee::Note("Character", character, __PRETTY_FUNCTION__),
                    ee::Note("Fontsize", fontSize, __PRETTY_FUNCTION__)
            }, ee::Stacktrace::create());
            return std::nullopt;
        }

        // Cast bitmap
        FT_BitmapGlyph bit = (FT_BitmapGlyph)glyph;

        // Make a copy of the buffer
        const uint8_t channels = 2;
        const size_t bufferSize = bit->bitmap.width * bit->bitmap.rows * channels;
        void* pData = malloc(bufferSize);
        memcpy(pData, bit->bitmap.buffer, bufferSize);

        // Create the bitmap
        auto bitmap = std::make_shared<gfx::Bitmap>(
                pData,
                bit->bitmap.width,
                bit->bitmap.rows,
                channels);

        // Create the character
        Character c(character,
                  static_cast<float>(this->mFaceHandle->glyph->advance.x >> 6),
                  static_cast<float>(-box.yMin),
                  static_cast<float>(this->mFaceHandle->glyph->metrics.horiBearingY >> 6),
                  bitmap);

        // Create CachedChar
        cache.emplace(character, c);

        // Done with this glyph
        FT_Done_Glyph(glyph);

        // Return a pointer to the character
        return &this->mCharacterCache.at(fontSize).at(character);
    }

    std::optional<Character*> Font::getCharacter(long character, font::size_t fontSize) noexcept {
        // Look in cache (fontSize -> character)
        if (this->mCharacterCache.count(fontSize)) {
            auto fs = this->mCharacterCache.at(fontSize);
            if (fs.count(character)) {
                return &fs.at(character);
            }
        }

        // Try to create the character
        return this->createCharacter(character, fontSize);
    }
}