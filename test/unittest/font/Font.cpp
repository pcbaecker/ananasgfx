#include "../Catch.hpp"
#include <ananasgfx/font/Font.hpp>
#include <ee/Log.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

TEST_CASE("font::Font") {
    // Reset the log
    ee::Log::reset();

    // Read the font file
    FT_Library  library = nullptr;
    REQUIRE(FT_Init_FreeType(&library) == 0);
    FT_Face face = nullptr;
    REQUIRE(FT_New_Face(library, "resource/Roboto-Bold.ttf", 0, &face) == 0);

    {// We need a scope for the font to be destroyed before the library is freed
        font::Font font(face, "MyFontFamily", "MyFontSubFamily");

        SECTION("const std::string& getFamilyName() const noexcept") {
            REQUIRE("MyFontFamily" == font.getFamilyName());
        }

        SECTION("const std::string& getSubFamilyName() const noexcept") {
            REQUIRE("MyFontSubFamily" == font.getSubFamilyName());
        }

        SECTION("bool createCharacter(long, font::size_t) noexcept") {

            SECTION("Recreate character") {
                REQUIRE(ee::Log::getNumberOfLogEntries() == 0);
                REQUIRE(font.createCharacter(static_cast<long>('A'), 12));
                REQUIRE(ee::Log::getNumberOfLogEntries() == 0);
                REQUIRE_FALSE(font.createCharacter(static_cast<long>('A'), 12));
                REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Warning] == 1);
            }

            SECTION("ASCII character 'A'") {
                const auto c = static_cast<long>('A');
                const font::size_t fs = 12;
                REQUIRE(font.createCharacter(c, fs));
                REQUIRE(font.getCharacterCache().count(fs) == 1);
                REQUIRE(font.getCharacterCache().at(fs).count(c) == 1);
                auto& character = font.getCharacterCache().at(fs).at(c);
                REQUIRE(character->getBitmap().getWidth() > 0);
                REQUIRE(character->getBitmap().getHeight() > 0);
                REQUIRE(character->getCharCode() == c);
            }

            SECTION("UTF-8 character 'ö'") {
                const long c = 0xF6;
                const font::size_t fs = 12;
                REQUIRE(font.createCharacter(c, fs));
                REQUIRE(font.getCharacterCache().count(fs) == 1);
                REQUIRE(font.getCharacterCache().at(fs).count(c) == 1);
                auto& character = font.getCharacterCache().at(fs).at(c);
                REQUIRE(character->getBitmap().getWidth() > 0);
                REQUIRE(character->getBitmap().getHeight() > 0);
                REQUIRE(character->getCharCode() == c);
            }
        }
    }

    // Destroy the library
    FT_Done_FreeType(library);
}