#ifndef TEST_APPLICATIONTEST_H
#define TEST_APPLICATIONTEST_H

#include "TestTasks.hpp"
#include "internal/ApplicationTestStore.hpp"

namespace test {

    class ApplicationTest {
    public:
        virtual void run() = 0;

        void setApplication(std::shared_ptr<gfx::Application> application) noexcept;

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
        std::shared_ptr<gfx::Application> mApplication;
    };

}


#define NN_UNIQUENAME(name, line) name##line
#define APPLICATION_TEST(appname) NN_TESTCLASS(NN_UNIQUENAME(ananasgfx_test,__COUNTER__), appname)

#define NN_TESTCLASS(classname, appname) \
class classname; \
test::_internal::ApplicationTestProxy<classname> NN_UNIQUENAME(ananasgfx_test_proxy, __COUNTER__)(appname); \
class classname : public test::ApplicationTest

#endif