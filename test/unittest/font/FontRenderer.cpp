#include "../Catch.hpp"
#include <ananasgfx/font/FontRenderer.hpp>
#include <map>

TEST_CASE("font::FontRenderer") {

    SECTION("std::vector<long> convert(const std::string& string) noexcept") {

        SECTION("Test invalid characters") {
            REQUIRE(font::FontRenderer::convert("\xf0\x90\x89").empty());
            REQUIRE(font::FontRenderer::convert("\xf0\x90").empty());
            REQUIRE(font::FontRenderer::convert("\xf0").empty());
            REQUIRE(font::FontRenderer::convert("\x90\x89").empty());
            REQUIRE(font::FontRenderer::convert("\xE2\x82").empty());
            REQUIRE(font::FontRenderer::convert("\xE2").empty());
            REQUIRE(font::FontRenderer::convert("\xC3").empty());
            REQUIRE(font::FontRenderer::convert("\xAE").empty());
            REQUIRE(font::FontRenderer::convert("\xFF").empty());
        }

        SECTION("Test the conversion of single characters") {
            // Prepare a map of utf8 characters and the expected conversion
            std::map<std::string,long> expected;
            expected["y"] = 0x0079;
            expected["\xC3\xA4"] = 0x00E4;
            expected["\xC2\xAE"] = 0x00AE;
            expected["\xE2\x82\xAC"] = 0x20AC;
            expected["\xF0\x9D\x84\x9E"] = 0x1D11E;
            expected["\xf0\x90\x8a\x8f"] = 0x1028F;
            expected["\xf0\x90\x89\xb5"] = 0x10275;

            // Go through all expectations
            for (auto& expect : expected) {
                auto r = font::FontRenderer::convert(expect.first);
                REQUIRE(r.size() == 1);
                REQUIRE(r[0] == expect.second);
            }
        }

        SECTION("Test the conversion of complete strings") {
            REQUIRE(font::FontRenderer::convert("Ümit Yaşar Oğuzcan").size() == 18);
            REQUIRE(font::FontRenderer::convert("بوابة بالحرب المزيفة ذلك").size() == 24);
            REQUIRE(font::FontRenderer::convert("速請連著提囲春受二位並本復済石計転旅証落").size() == 20);
        }
    }
}