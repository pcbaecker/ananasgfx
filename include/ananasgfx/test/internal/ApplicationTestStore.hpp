#ifndef TEST_INTERNAL_APPLICATIONTESTSTORE_H
#define TEST_INTERNAL_APPLICATIONTESTSTORE_H

#include <string>
#include <memory>
#include <list>
#include <map>

namespace gfx {
    class Application;
}

namespace test {

    class ApplicationTest;

    namespace _internal {

        class ApplicationTestProxyBase {
        public:
            explicit ApplicationTestProxyBase(const std::string &appname) noexcept;

            virtual std::shared_ptr<ApplicationTest>
            createInstance(std::shared_ptr<gfx::Application> application) noexcept = 0;
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
            explicit ApplicationTestProxy(const std::string &appname) noexcept :
            ApplicationTestProxyBase(appname), mAppname(appname) {}

            std::shared_ptr<ApplicationTest>
            createInstance(std::shared_ptr<gfx::Application> application) noexcept override {
                auto test = std::make_shared<T>();
                test->setApplication(this->mAppname, application);
                return test;
            }

        private:
            std::string mAppname;
        };

    }

}

#endif