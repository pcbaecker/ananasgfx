#include "../Catch.hpp"
#include <ananasgfx/test/PHash.hpp>
#include <iostream>

TEST_CASE("test::PHash") {

    SECTION("uint64_t hash(const gfx::Bitmap&) noexcept") {
        // Tree as jpg file
        auto treeJpgOpt = gfx::Bitmap::read("resource/tree.jpg");
        REQUIRE(treeJpgOpt.has_value());
        auto treeJpg = *treeJpgOpt;
        uint64_t treeJpgHash = test::PHash::hash(*treeJpg);

        // Tree as png file
        auto treePngOpt = gfx::Bitmap::read("resource/tree.png");
        REQUIRE(treePngOpt.has_value());
        auto treePng = *treePngOpt;
        uint64_t treePngHash = test::PHash::hash(*treePng);

        // Tree with a little diff as png
        auto treeDiffOpt = gfx::Bitmap::read("resource/treePhash.png");
        REQUIRE(treeDiffOpt.has_value());
        auto treeDiff = *treeDiffOpt;
        uint64_t treeDiffHash = test::PHash::hash(*treeDiff);

        // Completly different image
        auto otherOpt = gfx::Bitmap::read("resource/icon_lightbulb.png");
        REQUIRE(otherOpt.has_value());
        auto other = *otherOpt;
        uint64_t otherHash = test::PHash::hash(*other);

        // Compare the distances
        REQUIRE(test::PHash::distance(treeJpgHash,treePngHash) == 1);
        REQUIRE(test::PHash::distance(treeDiffHash,treePngHash) == 8);
        REQUIRE(test::PHash::distance(treeDiffHash,treeJpgHash) == 7);
        REQUIRE(test::PHash::distance(treePngHash,otherHash) == 43);
    }

    SECTION("std::vector<double> _dct(const std::vector<double> &) noexcept") {
        std::vector<double> time(4);
        time[0] = 255;
        time[1] = 128;
        time[2] = 55;
        time[3] = 99;
        auto freq = test::PHash::_dct(time);
        REQUIRE(freq.size() == 4);
        REQUIRE(freq[0] == Approx(537.0));
        REQUIRE(freq[1] == Approx(172.0610976344));
        REQUIRE(freq[2] == Approx(120.9152595829));
        REQUIRE(freq[3] == Approx(-7.7445904244));
    }

    SECTION("uint64_t _compareToThreshold(const std::vector<double> &, double) noexcept") {
        std::vector<double> vec(64);
        for (int i = 0; i < 64; i++) {
            vec[i] = i;
        }
        uint64_t result = test::PHash::_compareToThreshold(vec, 31.5);
        REQUIRE(result == 0xffffffff00000000);
    }

    SECTION("std::string toString(uint64_t) noexcept") {
        uint64_t hash = -1;
        auto str = test::PHash::toString(hash);
        REQUIRE(str == "1111111111111111111111111111111111111111111111111111111111111111");
    }

    SECTION("uint8_t distance(uint64_t, uint64_t) noexcept") {
        REQUIRE(test::PHash::distance(1,1) == 0);
        REQUIRE(test::PHash::distance(1,3) == 1);
        REQUIRE(test::PHash::distance(8,15) == 3);
    }
}