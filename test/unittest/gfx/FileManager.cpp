#include "../Catch.hpp"
#include <ananasgfx/gfx/FileManager.hpp>
#include <fstream>

TEST_CASE("gfx::FileManager") {

    gfx::FileManager fileManager("resource/", "user/");

    SECTION("std::string getUserfile(const std::string&) const noexcept") {
        REQUIRE("user/file.txt" == fileManager.getUserfile("file.txt"));
        REQUIRE("user/someother.log" == fileManager.getUserfile("someother.log"));
    }

    SECTION("std::string getResource(const std::string&) const noexcept") {
        REQUIRE("resource/file.txt" == fileManager.getResource("file.txt"));
        REQUIRE("resource/someother.log" == fileManager.getResource("someother.log"));
    }

    SECTION("std::optional<std::string> tryUserfile(const std::string&) const noexcept") {
        REQUIRE_FALSE(fileManager.tryUserfile("testfile.txt").has_value());

        // Create the file
        std::ofstream file(fileManager.getUserfile("testfile.txt"), std::ios::out);
        REQUIRE(file.is_open());
        file << "Some content";
        file.close();

        // Now we must find the file
        auto f = fileManager.tryUserfile("testfile.txt");
        REQUIRE(f.has_value());
        REQUIRE(*f == "user/testfile.txt");

        // Remove the file
        std::remove((*f).c_str());
    }

    SECTION("std::optional<std::string> tryResource(const std::string&) const noexcept") {
        REQUIRE_FALSE(fileManager.tryResource("unkown-resource.txt").has_value());
        auto file = fileManager.tryResource("Roboto-Bold.ttf");
        REQUIRE("resource/Roboto-Bold.ttf" == file);
    }

}