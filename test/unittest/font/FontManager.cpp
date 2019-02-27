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

    SECTION("bool registerFont(const std::string&)") {

        font::FontManager fontManager;

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
        }

        SECTION("Read fontFamily from file") {
            REQUIRE(fontManager.getFontFache().empty());
            REQUIRE(fontManager.registerFont("resource/Roboto-Bold.ttf"));
            REQUIRE(fontManager.getFontFache().size() == 1);
            REQUIRE(fontManager.getFontFache()[0].getFamilyName() == "Roboto");
            REQUIRE(fontManager.getFontFache()[0].getSubFamilyName() == "Bold");
        }
    }

    font::FontManager fontManager;
    REQUIRE(fontManager.getFontFache().empty());
    REQUIRE(fontManager.registerFont("resource/Roboto-Bold.ttf"));

    SECTION("const std::vector<Font>& getFontFache() const noexcept") {
        REQUIRE(fontManager.getFontFache().size() == 1);
        REQUIRE(fontManager.getFontFache()[0].getFamilyName() == "Roboto");
        REQUIRE(fontManager.getFontFache()[0].getSubFamilyName() == "Bold");
    }

    SECTION("std::optional<Font*> get(const std::string& family, const std::string& subfamily) noexcept") {
        // Search not existing font
        REQUIRE_FALSE(fontManager.get("unknown", "sub").has_value());

        REQUIRE(fontManager.get("Roboto", "Bold").has_value());
    }

}