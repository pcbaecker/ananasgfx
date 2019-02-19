#ifndef TEST_APPLICATIONTEST_H
#define TEST_APPLICATIONTEST_H

#include "TestTasks.hpp"
#include "internal/ApplicationTestStore.hpp"

namespace test {

    class ApplicationTest {
    public:
        ~ApplicationTest() noexcept;
        virtual void run() = 0;

        void setApplication(std::string name, std::shared_ptr<gfx::Application> application) noexcept;

    protected:
        void If(std::function<bool(gfx::Application *)> condition,
                std::function<void(gfx::Application *)> thenDo,
                std::function<void(gfx::Application *)> elseDo = nullptr);

        void Compare(const std::string& nodepath, const std::string& filepath);

        void Run(std::function<void(gfx::Application *)> task);

        template<class T> void Control(
                const std::string &nodepath,
                std::function<void(gfx::Application *, T *)> task) noexcept {
            this->mApplication->addTask(std::make_shared<test::Control<T>>(nodepath, task));
        }
    private:
        std::string mName;
        size_t mFailures = 0;
        size_t mSuccesses = 0;
        std::shared_ptr<gfx::Application> mApplication;
    };

}

#define REGISTER_APPLICATIONTEST(appname,appclass) \
test::_internal::ApplicationTestProxy<appclass> app_ ## appclass(appname) // NOLINT

#endif