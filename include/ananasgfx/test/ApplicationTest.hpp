#ifndef TEST_APPLICATIONTEST_H
#define TEST_APPLICATIONTEST_H

#include <string>
#include <memory>
#include <list>
#include <map>
#include <functional>

#include <ananasgfx/gfx/Task.hpp>

namespace gfx {
    class Application;
}

namespace test {

    class ApplicationTest;

    namespace _internal {

        class ApplicationTestProxyBase {
        public:
            explicit ApplicationTestProxyBase(const std::string &appname) noexcept;

            virtual std::shared_ptr<ApplicationTest> createInstance(std::shared_ptr<gfx::Application> application) noexcept = 0;
        };

        class ApplicationTestStore {
        public:
            static ApplicationTestStore &getInstance() noexcept;

            void registerApplicationTestProxy(const std::string &appname,
                                              ApplicationTestProxyBase *pApplicationTest) noexcept;

            size_t getNumberOfApplicationTests() const noexcept;

            const std::map<std::string, std::list<ApplicationTestProxyBase *>> getApplicationTests() const noexcept;

        private:
            ApplicationTestStore() noexcept;

        private:
            std::map<std::string, std::list<ApplicationTestProxyBase *>> mApplications;
        };

        template<class T>
        class ApplicationTestProxy : public ApplicationTestProxyBase {
        public:
            explicit ApplicationTestProxy(const std::string &appname) noexcept : ApplicationTestProxyBase(appname) {}

            std::shared_ptr<ApplicationTest> createInstance(std::shared_ptr<gfx::Application> application) noexcept override {
                auto test = std::make_shared<T>();
                test->setApplication(application);
                return test;
            }

        };

    }


    class IfTask : public gfx::Task {
    public:
        explicit IfTask(
                std::function<bool(gfx::Application*)> condition,
                std::function<void(gfx::Application*)> thenDo,
                std::function<void(gfx::Application*)> elseDo) noexcept;

        bool run(gfx::Application*) noexcept override;

    private:
        std::function<bool(gfx::Application*)> mCondition;
        std::function<void(gfx::Application*)> mThenDo;
        std::function<void(gfx::Application*)> mElseDo;
    };

    class ApplicationTest {
    public:
        virtual void run() = 0;
        void setApplication(std::shared_ptr<gfx::Application> application) noexcept;
    protected:
        void If(std::function<bool(gfx::Application*)> condition,
                std::function<void(gfx::Application*)> thenDo,
                std::function<void(gfx::Application*)> elseDo = nullptr);

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