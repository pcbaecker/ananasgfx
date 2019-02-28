#include "../../Catch.hpp"
#include <ananasgfx/gfx/internal/ApplicationStore.hpp>

TEST_CASE("gfx::_internal::ApplicationStore") {

    SECTION("ApplicationStore& getInstance() noexcept") {
        gfx::_internal::ApplicationStore::getInstance();
    }

    SECTION("void registerApplicationProxy(const std::string&, ApplicationProxyBase*) noexcept") {
        auto as = gfx::_internal::ApplicationStore::getInstance();
        REQUIRE(as.getNumberOfApplications() == 0);

        as.registerApplicationProxy("myapp", nullptr);
        REQUIRE(as.getNumberOfApplications() == 1);
        REQUIRE(as.getApplications().count("myapp") == 1);
        REQUIRE(as.getApplications().at("myapp") == nullptr);
    }

    SECTION("size_t getNumberOfApplications() const noexcept") {
        auto as = gfx::_internal::ApplicationStore::getInstance();
        REQUIRE(as.getNumberOfApplications() == 0);

        as.registerApplicationProxy("myapp", nullptr);
        REQUIRE(as.getNumberOfApplications() == 1);
    }

    SECTION("const std::map<std::string,ApplicationProxyBase*> getApplications() const noexcept") {
        auto as = gfx::_internal::ApplicationStore::getInstance();
        REQUIRE(as.getNumberOfApplications() == 0);

        as.registerApplicationProxy("myapp", nullptr);
        REQUIRE(as.getNumberOfApplications() == 1);
        REQUIRE(as.getApplications().count("myapp") == 1);
        REQUIRE(as.getApplications().at("myapp") == nullptr);
    }

}