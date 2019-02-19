#include <ananasgfx/font/FontManager.hpp>
#include <ee/Log.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../Catch.hpp"

TEST_CASE("font::FontManager") {

    // Reset logs
    ee::Log::reset();

    SECTION("static std::optional<std::tuple<std::string,std::string>> readFontFamily(FT_Face) noexcept") {
        // Read the font file
        FT_Library  library = nullptr;
        REQUIRE(FT_Init_FreeType(&library) == 0);
        FT_Face face = nullptr;
        REQUIRE(FT_New_Face(library, "resource/Roboto-Bold.ttf", 0, &face) == 0);

        // Read the file
        auto optional = font::FontManager::readFontFamily(face);
        REQUIRE(optional.has_value());
        REQUIRE(std::get<0>(*optional) == "Roboto");
        REQUIRE(std::get<1>(*optional) == "Bold");

        // Destroy the library
        FT_Done_Face(face);
        FT_Done_FreeType(library);
    }

    font::FontManager fontManager;
    fontManager.setHorizontalDpi(76.0f);
    fontManager.setVerticalDpi(72.0f);

    SECTION("bool registerFont(const std::string&)") {

        SECTION("File not found") {
            REQUIRE(ee::Log::getNumberOfLogEntries() == 0);
            REQUIRE_FALSE(fontManager.registerFont("unknown.ttf"));
            REQUIRE(ee::Log::countLogLevels()[ee::LogLevel::Error] == 1);
        }

        SECTION("With predefined fontFamily") {
            REQUIRE(fontManager.getFontFache().empty());
            REQUIRE(fontManager.registerFont("resource/Roboto-Bold.ttf", "MyFontFamily", "MyFontSubFamily"));
            REQUIRE(fontManager.getFontFache().size() == 1);
            REQUIRE(fontManager.getFontFache()[0].getFamilyName() == "MyFontFamily");
            REQUIRE(fontManager.getFontFache()[0].getSubFamilyName() == "MyFontSubFamily");
            REQUIRE(fontManager.getFontFache()[0].getHorizontalDpi() == Approx(76.0f));
            REQUIRE(fontManager.getFontFache()[0].getVerticalDpi() == Approx(72.0f));
        }

        SECTION("Read fontFamily from file") {
            REQUIRE(fontManager.getFontFache().empty());
            REQUIRE(fontManager.registerFont("resource/Roboto-Bold.ttf"));
            REQUIRE(fontManager.getFontFache().size() == 1);
            REQUIRE(fontManager.getFontFache()[0].getFamilyName() == "Roboto");
            REQUIRE(fontManager.getFontFache()[0].getSubFamilyName() == "Bold");
            REQUIRE(fontManager.getFontFache()[0].getHorizontalDpi() == Approx(76.0f));
            REQUIRE(fontManager.getFontFache()[0].getVerticalDpi() == Approx(72.0f));
        }
    }

    SECTION("const std::vector<Font>& getFontFache() const noexcept") {
        REQUIRE(fontManager.getFontFache().empty());
        REQUIRE(fontManager.registerFont("resource/Roboto-Bold.ttf"));
        REQUIRE(fontManager.getFontFache().size() == 1);
        REQUIRE(fontManager.getFontFache()[0].getFamilyName() == "Roboto");
        REQUIRE(fontManager.getFontFache()[0].getSubFamilyName() == "Bold");
        REQUIRE(fontManager.getFontFache()[0].getHorizontalDpi() == Approx(76.0f));
        REQUIRE(fontManager.getFontFache()[0].getVerticalDpi() == Approx(72.0f));
    }

}