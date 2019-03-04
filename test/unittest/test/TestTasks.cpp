#include "../Catch.hpp"
#include <ananasgfx/test/TestTasks.hpp>

TEST_CASE("test::IfTask") {
    int counter = 0;
    std::promise<bool> promise;
    auto future = promise.get_future();
    test::IfTask task([&](gfx::Application *) {
                          return true;
                      },
                      [&](gfx::Application *) {
        counter++;
        },
                      [&](gfx::Application *) {},
                      std::move(promise));

    SECTION("bool run(gfx::Application*) noexcept override") {
        REQUIRE(0 == counter);
        REQUIRE_FALSE(task.run(nullptr));
        REQUIRE(future.get());
        REQUIRE(1 == counter);
    }
}

TEST_CASE("test::Compare") {
    // Not testable without an active context
}

TEST_CASE("test::Task") {
    int counter = 0;
    test::Task task([&](gfx::Application*) {
        counter++;
    });

    SECTION("bool run(gfx::Application*) noexcept") {
        REQUIRE(0 == counter);
        REQUIRE_FALSE(task.run(nullptr));
        REQUIRE(1 == counter);
    }
}

TEST_CASE("test::Control") {
    // Not testable without an active context
}