#include <ananasgfx/test/ApplicationTest.hpp>
#include <ananasgfx/gfx/internal/ApplicationManager.hpp>

namespace test {

    ApplicationTest::~ApplicationTest() noexcept {
        std::cout << this->mName << " [ ";
        if (this->mFailures) {
            std::cout << "\033[1;31m FAIL \033[0m]" << std::endl;
            gfx::_internal::ApplicationManager::ReturnCode = EXIT_FAILURE;
        } else {
            std::cout << "\033[1;32mOK \033[0m]" << std::endl;
        }

        this->mApplication->addTask(std::make_shared<test::Task>([](gfx::Application* app) {
            app->close();
        }));
    }

    void ApplicationTest::setApplication(std::string name, std::shared_ptr<gfx::Application> application) noexcept {
        this->mName = std::move(name);
        this->mApplication = std::move(application);
    }

    void ApplicationTest::If(std::function<bool(gfx::Application*)> condition,
                             std::function<void(gfx::Application*)> thenDo,
                             std::function<void(gfx::Application*)> elseDo) {
        std::promise<bool> promise;
        auto future = promise.get_future();
        this->mApplication->addTask(std::make_shared<IfTask>(condition, thenDo, elseDo, std::move(promise)));
        if (future.get()) {
            this->mSuccesses++;
        } else {
            this->mFailures++;
        }
    }

    void ApplicationTest::Compare(const std::string &nodepath, const std::string &filepath) {
        std::promise<bool> promise;
        auto future = promise.get_future();
        this->mApplication->addTask(std::make_shared<test::Compare>(nodepath, filepath, std::move(promise)));
        if (future.get()) {
            this->mSuccesses++;
        } else {
            this->mFailures++;
        }
    }

    void ApplicationTest::Run(std::function<void(gfx::Application *)> task) {
        this->mApplication->addTask(std::make_shared<test::Task>(task));
    }

}