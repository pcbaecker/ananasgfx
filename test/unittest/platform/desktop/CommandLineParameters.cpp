#include "../../Catch.hpp"
#include <ananasgfx/platform/desktop/CommandLineParameters.hpp>

TEST_CASE("platform::desktop::CommandLineParameters") {

    SECTION("Construct empty") {
        const char* arguments[0];
        platform::desktop::CommandLineParameters clp(0, arguments);
        REQUIRE(clp.getCommands().empty());
    }

    SECTION("Construct with one boolean argument") {
        // Construct
        const char* arguments[] = {"--single-arg"};
        platform::desktop::CommandLineParameters clp(1, arguments);

        // Check
        REQUIRE(clp.getCommands().size() == 1);
        REQUIRE(clp.getCommands().count("single-arg"));
        REQUIRE(clp.getCommands().at("single-arg") == "true");
    }

    SECTION("Construct with one name value argument") {
        // Construct
        const char* arguments[] = {"--myname=my-value"};
        platform::desktop::CommandLineParameters clp(1, arguments);

        // Check
        REQUIRE(clp.getCommands().size() == 1);
        REQUIRE(clp.getCommands().count("myname"));
        REQUIRE(clp.getCommands().at("myname") == "my-value");
    }

    SECTION("Construct with multiple arguments") {
        // Construct
        const char* arguments[] = {
                "--some-name=some-value",
                "--capital123=CAPITAL",
                "--bool",
                "--integer=123",
                "--filepath=/path/to/logs/"};
        platform::desktop::CommandLineParameters clp(5, arguments);

        // Check
        REQUIRE(clp.getCommands().size() == 5);
        REQUIRE(clp.getCommands().count("some-name"));
        REQUIRE(clp.getCommands().at("some-name") == "some-value");
        REQUIRE(clp.getCommands().count("capital123"));
        REQUIRE(clp.getCommands().at("capital123") == "CAPITAL");
        REQUIRE(clp.getCommands().count("bool"));
        REQUIRE(clp.getCommands().at("bool") == "true");
        REQUIRE(clp.getCommands().count("integer"));
        REQUIRE(clp.getCommands().at("integer") == "123");
        REQUIRE(clp.getCommands().count("filepath"));
        REQUIRE(clp.getCommands().at("filepath") == "/path/to/logs/");
    }

    SECTION("const std::map<std::string,std::string>& getCommands() const noexcept") {
        const char* arguments[] = {"--single-arg"};
        platform::desktop::CommandLineParameters clp(1, arguments);
        REQUIRE(clp.getCommands().size() == 1);
        REQUIRE(clp.getCommands().count("single-arg"));
        REQUIRE(clp.getCommands().at("single-arg") == "true");
    }

    SECTION("std::string getString(const std::string&, const std::string&) const noexcept") {
        const char* arguments[] = {"--myname=my-value"};
        platform::desktop::CommandLineParameters clp(1, arguments);

        REQUIRE(clp.getString("myname", "") == "my-value");
        REQUIRE(clp.getString("anothervalue", "default") == "default");
    }

    SECTION("bool getBool(const std::string&, bool) const noexcept") {
        const char* arguments[] = {"--single-arg"};
        platform::desktop::CommandLineParameters clp(1, arguments);
        REQUIRE(clp.getBool("single-arg", false));
        REQUIRE(clp.getBool("unknown", true));
        REQUIRE_FALSE(clp.getBool("unknown", false));
    }

    SECTION("long getLong(const std::string&, long) const noexcept") {
        const char* arguments[] = {"--long=123", "--string=sss", "--string-with-int=123s"};
        platform::desktop::CommandLineParameters clp(2, arguments);
        REQUIRE(clp.getLong("long", 0) == 123);
        REQUIRE(clp.getLong("string", 55) == 55);
        REQUIRE(clp.getLong("string-with-int", 77) == 77);
        REQUIRE(clp.getLong("notexist", 66) == 66);
    }
}