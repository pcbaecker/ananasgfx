#include "../../Catch.hpp"
#include <ananasgfx/gfx/internal/ApplicationManager.hpp>
#include <ee/Log.hpp>

TEST_CASE("gfx::_internal::ApplicationManager") {

    ee::Log::reset();

    SECTION("void removeUnlisted(std::map<std::string,ApplicationProxyBase*>&,std::vector<std::string>&) noexcept") {
        SECTION("Normal case") {
            // Prepare
            std::map<std::string,gfx::_internal::ApplicationProxyBase*> mapOfApps;
            mapOfApps.emplace("firstapp", nullptr);
            mapOfApps.emplace("secondapp", nullptr);
            mapOfApps.emplace("thirdapp", nullptr);
            std::vector<std::string> appsToKeep = {"secondapp"};

            // Execute
            gfx::_internal::ApplicationManager::removeUnlisted(mapOfApps, appsToKeep);

            // Check
            REQUIRE(mapOfApps.size() == 1);
            REQUIRE(mapOfApps.count("secondapp"));
            REQUIRE(appsToKeep.empty());
        }

        SECTION("Try to keep app that doesnt exist") {
            // Prepare
            std::map<std::string,gfx::_internal::ApplicationProxyBase*> mapOfApps;
            mapOfApps.emplace("firstapp", nullptr);
            mapOfApps.emplace("secondapp", nullptr);
            mapOfApps.emplace("thirdapp", nullptr);
            std::vector<std::string> appsToKeep = {"firstapp", "notexist"};

            // Execute
            REQUIRE(ee::Log::countLogLevels().count(ee::LogLevel::Warning) == 0);
            gfx::_internal::ApplicationManager::removeUnlisted(mapOfApps, appsToKeep);
            REQUIRE(ee::Log::countLogLevels().count(ee::LogLevel::Warning) == 1);

            // Check
            REQUIRE(mapOfApps.size() == 1);
            REQUIRE(mapOfApps.count("firstapp"));
            REQUIRE(appsToKeep.size() == 1);
            REQUIRE(appsToKeep[0] == "notexist");
        }
    }

    gfx::_internal::ApplicationManager applicationManager(
            true,
            {"appname"},
            123,
            "resourcespace",
            "userspace",
            true,
            true);

    SECTION("void tick() noexcept") {
        // Because there are no applications to launch the tick() should do nothing
        applicationManager.tick();
    }

    SECTION("bool isDone() const noexcept") {
        // There are no applications to launch that means we are done
        REQUIRE(applicationManager.isDone());
    }

    SECTION("const std::shared_ptr<Application>& getCurrentApplication() noexcept") {
        // There are no applications launched
        REQUIRE(applicationManager.getCurrentApplication() == nullptr);
    }

}