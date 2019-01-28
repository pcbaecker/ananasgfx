#include "../Catch.hpp"
#include <ananasgfx/test/Test.hpp>

#include <iostream>

APPLICATION_TEST("apptest") {
public:
    std::string getDescription() noexcept override {
        return "Hallo";
    }
};




TEST_CASE("my") {

   REQUIRE(test::_internal::ApplicationTestStore::getInstance().getApplications().size() == 1);

}