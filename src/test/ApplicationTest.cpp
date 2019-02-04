#include <ananasgfx/test/ApplicationTest.hpp>

namespace test {

    void ApplicationTest::setApplication(std::shared_ptr<gfx::Application> application) noexcept {
        this->mApplication = std::move(application);
    }

    void ApplicationTest::If(std::function<bool(gfx::Application*)> condition,
                             std::function<void(gfx::Application*)> thenDo,
                             std::function<void(gfx::Application*)> elseDo) {
        this->mApplication->addTask(std::make_shared<IfTask>(condition, thenDo, elseDo));
    }

    void ApplicationTest::Compare(const std::string &nodepath, const std::string &filepath) {
        this->mApplication->addTask(std::make_shared<test::Compare>(nodepath, filepath));
    }

    void ApplicationTest::Run(std::function<void(gfx::Application *)> task) {
        this->mApplication->addTask(std::make_shared<test::Task>(task));
    }

}