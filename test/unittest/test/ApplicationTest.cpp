#include "../Catch.hpp"
#include <ananasgfx/test/ApplicationTest.hpp>

class MyApplication : public gfx::Application {
public:
    bool init() noexcept override { return true; }
};

class MyApplicationTest : public test::ApplicationTest {
public:
    void run() override {}
};

TEST_CASE("test::ApplicationTest") {

    MyApplicationTest applicationTest;

    SECTION("void setApplication(std::string, std::shared_ptr<gfx::Application>) noexcept") {
        auto app = std::make_shared<MyApplication>();
        applicationTest.setApplication("myapp", app);
    }

}