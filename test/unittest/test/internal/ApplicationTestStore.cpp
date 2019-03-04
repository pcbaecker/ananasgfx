#include "../../Catch.hpp"
#include <ananasgfx/test/internal/ApplicationTestStore.hpp>

TEST_CASE("test::_internal::ApplicationTestStore") {

    SECTION("static ApplicationTestStore &getInstance() noexcept") {
        REQUIRE(0 == test::_internal::ApplicationTestStore::getInstance().getNumberOfApplicationTests());
    }

    auto store = test::_internal::ApplicationTestStore::getInstance();

    SECTION("void registerApplicationTestProxy(const std::string&,ApplicationTestProxyBase*) noexcept") {
        // Not testable
    }

    SECTION("size_t getNumberOfApplicationTests() const noexcept") {
        REQUIRE(0 == store.getNumberOfApplicationTests());
    }

    SECTION("const std::map<std::string, std::list<ApplicationTestProxyBase *>> getApplicationTests() const noexcept") {
        REQUIRE(store.getApplicationTests().empty());
    }

}