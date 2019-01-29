#ifndef TEST_APPLICATIONTEST_H
#define TEST_APPLICATIONTEST_H

#include <string>
#include <memory>
#include <list>
#include <map>

namespace test {

    class ApplicationTest {
    public:
        virtual std::string getDescription() noexcept = 0;
    };

    namespace _internal {

        class ApplicationTestProxyBase {
        public:
            explicit ApplicationTestProxyBase(const std::string& appname) noexcept;
            virtual std::shared_ptr<ApplicationTest> createInstance() noexcept = 0;
        };

        class ApplicationTestStore {
        public:
            static ApplicationTestStore& getInstance() noexcept;

            void registerApplicationTestProxy(const std::string& appname, ApplicationTestProxyBase *pApplicationTest) noexcept;
            size_t getNumberOfApplicationTests() const noexcept;
            const std::map<std::string,std::list<ApplicationTestProxyBase*>> getApplicationTests() const noexcept;

        private:
            ApplicationTestStore() noexcept;

        private:
            std::map<std::string,std::list<ApplicationTestProxyBase*>> mApplications;
        };

        template <class T> class ApplicationTestProxy : public ApplicationTestProxyBase {
        public:
            explicit ApplicationTestProxy(const std::string& appname) noexcept : ApplicationTestProxyBase(appname) {}
            std::shared_ptr<ApplicationTest> createInstance() noexcept override {
                return std::make_shared<T>();
            }

        };

    }

}





#define NN_UNIQUENAME(name,line) name##line
#define APPLICATION_TEST(appname) NN_TESTCLASS(NN_UNIQUENAME(ananasgfx_test,__COUNTER__), appname)

#define NN_TESTCLASS(classname, appname) \
class classname; \
test::_internal::ApplicationTestProxy<classname> NN_UNIQUENAME(ananasgfx_test_proxy, __COUNTER__)(appname); \
class classname : public test::ApplicationTest

#endif