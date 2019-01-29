#include "../Catch.hpp"
#include <ananasgfx/test/ApplicationTest.hpp>

APPLICATION_TEST("apptest") {
public:
    std::string getDescription() noexcept override {
        return "Hallo";
    }
};

TEST_CASE("test::ApplicationTest") {
    // TODO Write unittest for test::ApplicationTest
}

TEST_CASE("test::_internal::ApplicationTestStore") {

    REQUIRE(test::_internal::ApplicationTestStore::getInstance().getApplicationTests().size() == 1);
    REQUIRE(test::_internal::ApplicationTestStore::getInstance().getApplicationTests().count("apptest") == 1);
    REQUIRE(test::_internal::ApplicationTestStore::getInstance().getApplicationTests().at("apptest").size() == 1);

}